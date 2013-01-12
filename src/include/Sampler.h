/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __SAMPLER_H__
#define __SAMPLER_H__

#include "Wave.h"
#include "Frame.h"

typedef struct {
	Wave* wave;
	double start_time;
	double finish_time;
	double delta_time;
	double current_time;
} Sampler;

void nami_init_sampler(Sampler* sampler,
			Wave* wave,
			double start_time,
			double finish_time,
			uint32_t sampling_frequency);

void nami_set_sample_interval(Sampler* sampler, double start_time, double finish_time);

void nami_set_current_sample_time(Sampler* sampler, double current_time);

Frame* nami_fill_frame(Sampler* sampler, Frame* frame);

uint32_t nami_samples_left(Sampler* sampler);

#endif
