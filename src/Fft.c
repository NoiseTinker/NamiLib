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
static void copyDataToSpectrum();
static void copyDataToFrame();

void fft(Frame* frame, ComplexNumber* spectrum)
{
	uint16_t numFrequencies = frameSize(frame)/2;
	int ip[(2 + (int)ceil(sqrt(numFrequencies)))];
	double w[numFrequencies];
	ip[0] = 0;

	assert(sizeof(ComplexNumber) * 2 == sizeof(double) * 4);

	copyDataToSpectrum(frame, spectrum);

	// Call Ooura Complex Discrete Fourier Transform
	cdft(frameSize(frame), 1, (double*)spectrum, ip, w);
}

void ifft(ComplexNumber* spectrum, Frame* frame)
{
	uint16_t numFrequencies = frameSize(frame)/2;
	int ip[(2 + (int)ceil(sqrt(numFrequencies)))];
	double w[numFrequencies];
	ip[0] = 0;

	// Call Ooura Complex Discrete Fourier Transform
	cdft(frameSize(frame), -1, (double*)spectrum, ip, w);

	for (int j = 0; j <= frameSize(frame) - 1; j++) {
		spectrum[j].r *= 1.0 / numFrequencies;
	}

	copyDataToFrame(spectrum, frame);
}

static void copyDataToSpectrum(Frame* frame, ComplexNumber* spectrum)
{
	uint16_t size = frameSize(frame);
	double* data = frameDoubleData(frame);

	for (int i = 0; i < size; i++) {
		spectrum[i].r = data[i];
		spectrum[i].i = 0;
	}
}

static void copyDataToFrame(ComplexNumber* spectrum, Frame* frame)
{
	uint16_t size = frameSize(frame);
	double* data = frameDoubleData(frame);

	for (int i = 0; i < size; i++) {
		data[i] = spectrum[i].r;
	}
}


