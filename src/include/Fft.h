/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __FFT_H__
#define __FFT_H__

#include "Frame.h"
#include "ComplexNumber.h"

/*
* The parameter frame needs to point to a initiated Frame
* with encoding DOUBLE. Size must me 2^n.
*
* The parameter spectrum needs to point to an array of
* ComplexNumber with same number of elements as the
* frame size.
*
* Note: Assumes Frame is full. If needs zero padding should be done before call.
*
*/

typedef struct {
   double freq;
   double amplitude;
   double phase;
} SpectrumFreqency;

void nami_fft(Frame* frame, ComplexNumber* f_coefs);

void nami_ifft(ComplexNumber* f_coefs, Frame* frame);

/*
* The parameter spectrum needs to point to an array of SpectrumFreqency
* with size number of freqs in spectrum (floor(nbr_samples/2) + 1(DC))
*/

typedef struct {
	SpectrumFreqency* 	freqs;
	ComplexNumber* 		f_coefs;
	uint32_t sampling_frequency;
	size_t nbr_samples;
} PowerSpectrum;

PowerSpectrum* nami_init_spectrum(PowerSpectrum* spectrum, SpectrumFreqency* freqs, ComplexNumber* f_coefs, uint32_t sampling_frequency, size_t nbr_samples);

double nami_fft_top_freq(uint32_t sampling_frequency, size_t nbr_samples);

size_t nami_fft_top_index(size_t nbr_samples);

double nami_freq_at_index(int index);

#endif
