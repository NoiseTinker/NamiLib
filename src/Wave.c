/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Wave.h"
#include "Periodic.h"
#include <stdio.h>

double waveY(Wave* wave, double x, double t)
{
	return wave->amplitude * wave->func->func(wave->wavenumber*x + wave->angularFrequency*t + wave->phase);
}

void addPeriodic(Wave* wave, Periodic* func,
	double amplitude, double phase,
	double wavenumber, double angularFrequency)
{
	wave->func = func;
	wave->amplitude = amplitude;
	wave->phase = phase;
	wave->wavenumber = wavenumber;
	wave->angularFrequency = angularFrequency;
}

void clearWave(Wave* wave)
{
	wave->func = NULL;
	wave->amplitude = 0;
	wave->phase = 0;
	wave->wavenumber = 0;
	wave->angularFrequency = 0;
}

double angularFrequencyFromFrequency(double frequency)
{
	return 0;
}

double waveNumberFromWaveLength(double wavelength)
{
	return 0;
}
