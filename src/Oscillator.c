/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A complex (IQ signal) oscillator.
*/

#include <math.h>
#include "Oscillator.h"

void nami_osc_init(Oscillator* oscillator,
                        double angular_frequency,
                        uint32_t sampling_frequency)
{
	oscillator->angular_frequency = angular_frequency;
	oscillator->delta_time = 1.0 / sampling_frequency;
	oscillator->current_time = 0;
}

double nami_osc_y(Oscillator* oscillator)
{
	return cos(oscillator->angular_frequency * oscillator->current_time);
}

ComplexNumber nami_osc_cy(Oscillator* oscillator)
{
	ComplexNumber cy;
	cy.r = nami_osc_y(oscillator);
	cy.i = sin(oscillator->angular_frequency * oscillator->current_time);
	return cy;
}

void nami_osc_tick(Oscillator* oscillator)
{
	double new_time = oscillator->current_time + oscillator->delta_time;

	if (new_time * oscillator->angular_frequency <= 2*M_PI) {
		oscillator->current_time = new_time;
	} else {
		new_time -=  (2*M_PI) / oscillator->angular_frequency;
	}

	oscillator->current_time = new_time;
}

//Frame* nami_osc_fill_frame(Oscillator* oscillator, Frame* frame);

//ComplexFrame* nami_osc_fill_cframe(Oscillator* oscillator, ComplexFrame* frame);
