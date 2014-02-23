/*  
 * Copyright 2014 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 *
 * Applies a fixed gain to a frame.
 */

#ifndef __GAIN_H__
#define __GAIN_H__

#include "Frame.h"

#include <stdbool.h>
#include <float.h>

typedef struct {
        float avg_dBFS;
        double offset;
} Gain;

typedef struct {
	bool didClip;
	float peak_dBFS;
} GainResult;

Gain* nami_init_gain(Gain* gain);

void nami_apply_gain(Gain* gain, Frame* frame, float gain_dB, GainResult* result);

double nami_gain_factor(float gain_dB);

float nami_level_from_uint8(uint8_t value);

float nami_level_from_sint16(int16_t value);

float nami_level_from_float(float value);

float nami_level_from_double(double value);

uint8_t nami_apply_gain_uint8(uint8_t value, double gainFactor);

int16_t nami_apply_gain_sint16(int16_t value, double gainFactor);

float nami_apply_gain_float(float value, double gainFactor);

double nami_apply_gain_double(double value, double gainFactor);

#endif
