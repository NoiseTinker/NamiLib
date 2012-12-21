/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* The parameter spectrum needs to point to an array of
* ComplexNumber with same number of elements as the
* frame size.
*/

#ifndef __FFT_H__
#define __FFT_H__

#include "Frame.h"
#include "ComplexNumber.h"

void fft(Frame* frame, ComplexNumber* spectrum);

void ifft(ComplexNumber* spectrum, Frame* frame);

#endif
