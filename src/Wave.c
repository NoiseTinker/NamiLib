/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Wave.h"
#include "Periodic.h"
#include <stdio.h>
#include <math.h>

double nami_wave_y(Wave* wave, double t)
{	
	double y = wave->amplitude * wave->periodic->func(wave->angular_frequency*t + wave->phase);
	double envelope = 1;

	if (wave->envelope != NULL && wave->envelope->func != NULL) {
		envelope = wave->envelope->func(t, wave->envelope->data);
	}
	
	return envelope * y;;
}

bool nami_set_periodic(Wave* wave, Periodic* periodic,
	double amplitude, double phase,
	double angular_frequency)
{
	wave->periodic = periodic;
	wave->amplitude = amplitude;
	wave->phase = phase;
	wave->angular_frequency = angular_frequency;

	return true;
}

void nami_set_envelope(Wave* wave, Envelope* envelope)
{
	wave->envelope = envelope;
}

void nami_clear_wave(Wave* wave)
{
	wave->periodic = NULL;
	wave->amplitude = 0;
	wave->phase = 0;
	wave->angular_frequency = 0;
}

double nami_angular_frequency_from_frequency(double frequency)
{
	return 2 * M_PI * frequency;
}

double nami_angular_frequency_from_period(double period)
{
	return (2 * M_PI) / period;
}

