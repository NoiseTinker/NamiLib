/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Envelope.h"

double envelopeY(Envelope* env, double t)
{
	return env->func(t, env->data);
}

void addEnvelopeFunction(Envelope* env, double (*func)(double, void*), void* data)
{
	env->func = func;
	env->data = data;
}

double adsr(double t, void* data)
{
	AdsrParamters* params = (AdsrParamters*)data;

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

double gaussian(double t, void* data)
{
	return 0;
}
