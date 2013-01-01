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
	double sampleStartTime;
	double sampleFinishTime;
	double deltaTime;
	double currentTime;
} Sampler;

void initSampler(Sampler* sampler,
			Wave* wave,
			double sampleStartTime,
			double sampleFinishTime,
			uint32_t samplingFrequency);

void setSampleInterval(Sampler* sampler, double sampleStartTime, double sampleFinishTime);

void setCurrentSampleTime(Sampler* sampler, double currentTime);

Frame* fillFrame(Sampler* sampler, Frame* frame);

uint32_t samplesLeft(Sampler* sampler);

#endif
