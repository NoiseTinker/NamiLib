/*  
 * Copyright 2014 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 *
 * Applies a fixed gain to a frame.
 */

#include "Gain.h"

#include <math.h>
#include <stdlib.h>

#include <stdio.h> // test

Gain* nami_init_gain(Gain* gain)
{
	gain->avg_dBFS = 0;
	gain->offset = 0;
	return gain;
}

void nami_apply_gain(Gain* gain, Frame* frame, float gain_dB, GainResult* result)
{
	double gainFactor = nami_gain_factor(gain_dB);

	for (int i = 0; i < frame->used; i++) {
		switch(frame->encoding) {
			case UINT8:
			((uint8_t*)frame->data)[i] = nami_apply_gain_uint8(((uint8_t*)frame->data)[i], gainFactor);
			break;
			case SINT16:
			((int16_t*)frame->data)[i] = nami_apply_gain_sint16(((int16_t*)frame->data)[i], gainFactor);
			break;
			case FLOAT:
			((float*)frame->data)[i] = nami_apply_gain_float(((float*)frame->data)[i], gainFactor);
			break;
			case DOUBLE:
			((double*)frame->data)[i] = nami_apply_gain_float(((double*)frame->data)[i], gainFactor);
			break;
			default:
			break;
		}
	}
}

double nami_gain_factor(float gain_dB)
{
	return pow(10.0, (gain_dB/20.0));
}

float nami_level_from_uint8(uint8_t value)
{
	float absVal = 0;

	if (value > (UINT8_MAX / 2.0)) {
		absVal = value - (UINT8_MAX / 2.0);
	} else {
		absVal = (UINT8_MAX / 2.0) - value;
	}
	return 20 * log10(absVal / (UINT8_MAX / 2.0));
}

float nami_level_from_sint16(int16_t value)
{
	return 20 * log10(abs(value) / INT16_MAX);
}

float nami_level_from_float(float value)
{
	return 20 * log10(fabs(value) / 1);
}

float nami_level_from_double(double value)
{
	return 20 * log10(fabs(value) / 1);
}

uint8_t nami_apply_gain_uint8(uint8_t value, double gainFactor)
{
	float deviation = value - (UINT8_MAX / 2);
	deviation = deviation * gainFactor;
	return (UINT8_MAX / 2) + deviation;
}

int16_t nami_apply_gain_sint16(int16_t value, double gainFactor)
{
	return value * gainFactor;
}

float nami_apply_gain_float(float value, double gainFactor)
{
	return value * gainFactor;
}

double nami_apply_gain_double(double value, double gainFactor)
{
	return value * gainFactor;
}

