/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Envelope.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double envelopeY(Envelope* env, double t)
{
	return env->func(t, env->data);
}

void setEnvelopeFunction(Envelope* env, double (*func)(double, void*), void* data)
{
	env->func = func;
	env->data = data;
}

double adsr(double t, void* data)
{
	AdsrParameters* params = (AdsrParameters*)data;

	double totalTime;
	double result = 0;

	if (t < (totalTime = params->attackTime)) {
		result = t / params->attackTime;
	} else if (t < ((totalTime = totalTime + params->decayTime))) {
		result = 1 - (1 - params->sustainLevel) * ((t - params->attackTime) / params->decayTime);
	} else if (t < ((totalTime = totalTime + params->sustainTime))) {
		result = params->sustainLevel;
	} else if (t < ((totalTime = totalTime + params->releaseTime))) {
		result = params->sustainLevel * (1 - ((t - params->attackTime - params->decayTime - params->sustainTime) / params->releaseTime));
	}

	return result;
}

double raisedCosine(double t, void* data)
{
	RaisedCosineParameters* params = (RaisedCosineParameters*)data;

	double totalTime = params->riseTime + params->fallTime + params->sustainTime;
	double result = 0;

	if(t > 0 && t < totalTime) {

		if(t < params->riseTime) {
			// Rise
			result = 0.5 * (1 + cos(M_PI*(t/params->riseTime) - M_PI));
		} else if (t > params->riseTime + params->sustainTime) {
			// Fall
			result = 0.5 * (1 + cos(M_PI*((t - params->riseTime + params->sustainTime)/params->fallTime)));
		} else {
			result = 1;
		}
	}

	return result;
}
