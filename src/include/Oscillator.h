/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A complex (IQ signal) oscillator.
*/

#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

#include <stdint.h>
#include "Periodic.h"
#include "ComplexNumber.h"
//#include "Frame.h"
//#include "ComplexFrame.h"

typedef struct {
	double angular_frequency;
	double delta_time;
	double current_time;
} Oscillator;

void nami_osc_init(Oscillator* oscillator,
                        double angular_frequency,
                        uint32_t sampling_frequency);

double nami_osc_y(Oscillator* oscillator);

ComplexNumber nami_osc_cy(Oscillator* oscillator);

void nami_osc_tick(Oscillator* oscillator);

//Frame* nami_osc_fill_frame(Oscillator* oscillator, Frame* frame);

//ComplexFrame* nami_osc_fill_cframe(Oscillator* oscillator, ComplexFrame* frame);

#endif
