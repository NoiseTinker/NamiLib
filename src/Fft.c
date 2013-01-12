/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* The parameter spectrum needs to point to an array of
* ComplexNumber with same number of elements as the
* frame size.
*/

#include <math.h>
#include <assert.h>
#include "Fft.h"

extern void cdft(int, int, double *, int *, double *);
static void copy_to_spectrum();
static void copy_to_frame();

void nami_fft(Frame* frame, ComplexNumber* spectrum)
{
	uint16_t numFrequencies = nami_frame_size(frame)/2;
	int ip[(2 + (int)ceil(sqrt(numFrequencies)))];
	double w[numFrequencies];
	ip[0] = 0;

	assert(sizeof(ComplexNumber) * 2 == sizeof(double) * 4);

	copy_to_spectrum(frame, spectrum);

	// Call Ooura Complex Discrete Fourier Transform
	cdft(nami_frame_size(frame), 1, (double*)spectrum, ip, w);
}

void nami_ifft(ComplexNumber* spectrum, Frame* frame)
{
	uint16_t numFrequencies = nami_frame_size(frame)/2;
	int ip[(2 + (int)ceil(sqrt(numFrequencies)))];
	double w[numFrequencies];
	ip[0] = 0;

	// Call Ooura Complex Discrete Fourier Transform
	cdft(nami_frame_size(frame), -1, (double*)spectrum, ip, w);

	for (int j = 0; j <= nami_frame_size(frame) - 1; j++) {
		spectrum[j].r *= 1.0 / numFrequencies;
	}

	copy_to_frame(spectrum, frame);
}

static void copy_to_spectrum(Frame* frame, ComplexNumber* spectrum)
{
	uint16_t size = nami_frame_size(frame);
	double* data = nami_frame_double(frame);

	for (int i = 0; i < size; i++) {
		spectrum[i].r = data[i];
		spectrum[i].i = 0;
	}
}

static void copy_to_frame(ComplexNumber* spectrum, Frame* frame)
{
	uint16_t size = nami_frame_size(frame);
	double* data = nami_frame_double(frame);

	for (int i = 0; i < size; i++) {
		data[i] = spectrum[i].r;
	}
}


