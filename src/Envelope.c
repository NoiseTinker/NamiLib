/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Envelope.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double nami_envelope_y(Envelope* env, double t)
{
	return env->func(t, env->data);
}

void nami_set_envelope_function(Envelope* env, double (*func)(double, void*), void* data)
{
	env->func = func;
	env->data = data;
}

double nami_adsr(double t, void* data)
{
	AdsrParameters* params = (AdsrParameters*)data;

	double total_time;
	double result = 0;

	if (t < (total_time = params->attack_time)) {
		result = t / params->attack_time;
	} else if (t < ((total_time = total_time + params->decay_time))) {
		result = 1 - (1 - params->sustain_level) * ((t - params->attack_time) / params->decay_time);
	} else if (t < ((total_time = total_time + params->sustain_time))) {
		result = params->sustain_level;
	} else if (t < ((total_time = total_time + params->release_time))) {
		result = params->sustain_level * (1 - ((t - params->attack_time - params->decay_time - params->sustain_time) / params->release_time));
	}

	return result;
}

double nami_raised_cosine(double t, void* data)
{
	RaisedCosineParameters* params = (RaisedCosineParameters*)data;

	double total_time = params->rise_time + params->fall_time + params->sustain_time;
	double result = 0;

	if(t > 0 && t < total_time) {

		if(t < params->rise_time) {
			// Rise
			result = 0.5 * (1 + cos(M_PI*(t/params->rise_time) - M_PI));
		} else if (t > params->rise_time + params->sustain_time) {
			// Fall
			result = 0.5 * (1 + cos(M_PI*((t - params->rise_time + params->sustain_time)/params->fall_time)));
		} else {
			result = 1;
		}
	}

	return result;
}
