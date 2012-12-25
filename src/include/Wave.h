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
	double angularFrequency;
	Envelope* envelope;
} Wave;

double waveY(Wave* wave, double t);

/*
 * See https://en.wikipedia.org/wiki/Wave#Sinusoidal_waves
 */
bool setPeriodic(Wave* wave, Periodic* periodic,
	double amplitude, double phase,
	double angularFrequency);

void setEnvelope(Wave* wave, Envelope* envelope);

void clearWave(Wave* wave);

double angularFrequencyFromFrequency(double frequency);

#endif
