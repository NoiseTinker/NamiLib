/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* Demodulator of I/Q signals.
*/

#ifndef __DEMODULATOR_H__
#define __DEMODULATOR_H__

#include "Frame.h"
#include "Oscillator.h"

typedef struct {
	Oscillator* bfo;
	double (*func)(Oscillator* bfo, double, double);
} Demodulator;

void nami_demod_init(Demodulator* demod, Oscillator* bfo, double (*func)(Oscillator* bfo, double, double));

void nami_demod_frame(Demodulator* demod, Frame* src_frame, Frame* dst_frame);

double nami_demod_usb(Oscillator* bfo, double i, double q);

double nami_demod_lsb(Oscillator* bfo, double i, double q);

double nami_demod_am(Oscillator* bfo, double i, double q);

double nami_demod_fm(Oscillator* bfo, double i, double q);

#endif
