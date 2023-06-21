/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* The parameter frame needs to point to a initiated Frame
* with encoding DOUBLE.
*
* The parameter spectrum needs to point to an array of
* ComplexNumber with same number of elements as the
* frame size.
*/

#ifndef __FFT_H__
#define __FFT_H__

#include "Frame.h"
#include "ComplexNumber.h"

void nami_fft(Frame* frame, ComplexNumber* fCoeffs);

void nami_ifft(ComplexNumber* fCoeffs, Frame* frame);

double nami_fft_top_freq(uint32_t sampling_frequency, uint32_t nbr_samples);

#endif
