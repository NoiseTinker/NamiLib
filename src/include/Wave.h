/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __WAVE_H__
#define __WAVE_H__

#include "Periodic.h"
#include "Envelope.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	Periodic* periodic;
	double amplitude;
	double phase;
	double angular_frequency;
	Envelope* envelope;
} Wave;

double nami_wave_y(Wave* wave, double t);

/*
 * See https://en.wikipedia.org/wiki/Wave#Sinusoidal_waves
 */
bool nami_set_periodic(Wave* wave, Periodic* periodic,
	double amplitude, double phase,
	double angular_frequency);

void nami_set_envelope(Wave* wave, Envelope* envelope);

void nami_clear_wave(Wave* wave);

double nami_angular_frequency_from_frequency(double frequency);

double nami_angular_frequency_from_period(double period);

#endif
