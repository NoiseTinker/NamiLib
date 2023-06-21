/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* The parameter fCoeffs needs to point to an array of
* ComplexNumber with same number of elements as the
* frame size.
*/

#include <math.h>
#include <assert.h>
#include "Fft.h"

extern void cdft(int, int, double *, int *, double *);
static void nami_copy_to_coeffs();
static void nami_copy_to_frame();

void nami_fft(Frame* frame, ComplexNumber* fCoeffs)
{
	uint16_t numFrequencies = nami_frame_size(frame)/2;
	int ip[(2 + (int)ceil(sqrt(numFrequencies)))];
	double w[numFrequencies];
	ip[0] = 0;

	assert(sizeof(ComplexNumber) * 2 == sizeof(double) * 4);

	nami_copy_to_coeffs(frame, fCoeffs);

	// Call Ooura Complex Discrete Fourier Transform
	cdft(nami_frame_size(frame), 1, (double*)fCoeffs, ip, w);
}

void nami_ifft(ComplexNumber* fCoeffs, Frame* frame)
{
	uint16_t numFrequencies = nami_frame_size(frame)/2;
	int ip[(2 + (int)ceil(sqrt(numFrequencies)))];
	double w[numFrequencies];
	ip[0] = 0;

	// Call Ooura Complex Discrete Fourier Transform
	cdft(nami_frame_size(frame), -1, (double*)fCoeffs, ip, w);

	for (int j = 0; j <= nami_frame_size(frame) - 1; j++) {
		fCoeffs[j].r *= 1.0 / numFrequencies;
	}

	nami_copy_to_frame(fCoeffs, frame);
}

double nami_fft_top_freq(uint32_t sampling_frequency, uint32_t nbr_samples)
{
	double correction = nbr_samples % 2 == 0 ? 1 : ((double)nbr_samples - 1) / nbr_samples;
	return (sampling_frequency / 2) * correction;
}

static void nami_copy_to_coeffs(Frame* frame, ComplexNumber* fCoeffs)
{
	uint16_t size = nami_frame_size(frame);
	double* data = nami_frame_double(frame);

	for (int i = 0; i < size; i++) {
		fCoeffs[i].r = data[i];
		fCoeffs[i].i = 0;
	}
}

static void nami_copy_to_frame(ComplexNumber* fCoeffs, Frame* frame)
{
	uint16_t size = nami_frame_size(frame);
	double* data = nami_frame_double(frame);

	for (int i = 0; i < size; i++) {
		data[i] = fCoeffs[i].r;
	}
}
