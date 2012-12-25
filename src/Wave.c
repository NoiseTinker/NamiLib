/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Wave.h"
#include "Periodic.h"
#include <stdio.h>

double waveY(Wave* wave, double t)
{	
	double y = wave->amplitude * wave->periodic->func(wave->angularFrequency*t + wave->phase);
	double envelope = 1;

	if (wave->envelope != NULL && wave->envelope->func != NULL) {
		envelope = wave->envelope->func(t, wave->envelope->data);
	}
	
	return envelope * y;;
}

bool addPeriodic(Wave* wave, Periodic* periodic,
	double amplitude, double phase,
	double angularFrequency)
{
	wave->periodic = periodic;
	wave->amplitude = amplitude;
	wave->phase = phase;
	wave->angularFrequency = angularFrequency;

	return true;
}

void addEnvelope(Wave* wave, Envelope* envelope)
{
	wave->envelope = envelope;
}

void clearWave(Wave* wave)
{
	wave->periodic = NULL;
	wave->amplitude = 0;
	wave->phase = 0;
	wave->angularFrequency = 0;
}

double angularFrequencyFromFrequency(double frequency)
{
	return 0;
}
