/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __WAVE_H__
#define __WAVE_H__

#include "Periodic.h"

typedef struct {
	Periodic* func;
	double amplitude;
	double phase;
	double wavenumber;
	double angularFrequency;
} Wave;

double waveY(Wave* wave, double x, double t);

/*
 * See https://en.wikipedia.org/wiki/Wave#Sinusoidal_waves
 */
void addPeriodic(Wave* wave, Periodic* func,
	double amplitude, double phase,
	double wavenumber, double angularFrequency);

void clearWave(Wave* wave);

double angularFrequencyFromFrequency(double frequency);

double waveNumberFromWaveLength(double wavelength);

#endif
