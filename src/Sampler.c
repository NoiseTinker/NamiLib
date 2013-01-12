/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Sampler.h"

static double get_next_sample(Sampler* sampler);

void nami_init_sampler(Sampler* sampler,
			Wave* wave,
			double start_time,
			double finish_time,
			uint32_t sampling_frequency)
{
	sampler->wave = wave;
	sampler->start_time = start_time;
	sampler->finish_time = finish_time;
	sampler->current_time = start_time;
	sampler->delta_time = 1.0 / sampling_frequency;
}

void nami_set_sample_interval(Sampler* sampler, double start_time, double finish_time)
{
	sampler->start_time = start_time;
	sampler->finish_time = finish_time;
}

void nami_set_current_sample_time(Sampler* sampler, double current_time)
{
	sampler->current_time = current_time;
}

Frame* nami_fill_frame(Sampler* sampler, Frame* frame)
{

	for (uint32_t i = 0; i < frame->size
			&& sampler->current_time <= sampler->finish_time; i++) {

		double value = get_next_sample(sampler);
		nami_frame_write_sample(frame, value, i);
	}

	return frame;
}

uint32_t nami_samples_left(Sampler* sampler)
{
	return (sampler->finish_time - sampler->current_time) / sampler->delta_time;
}

static double get_next_sample(Sampler* sampler)
{
	double value = 0;

	value = nami_wave_y(sampler->wave, sampler->current_time);
	sampler->current_time += sampler->delta_time;

	return value;
}

