/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Sampler.h"

static double getNextSample(Sampler* sampler);

void initSampler(Sampler* sampler,
			Wave* wave,
			double sampleStartTime,
			double sampleFinishTime,
			uint32_t samplingFrequency)
{
	sampler->wave = wave;
	sampler->sampleStartTime = sampleStartTime;
	sampler->sampleFinishTime = sampleFinishTime;
	sampler->currentTime = sampleStartTime;
	sampler->deltaTime = 1.0 / samplingFrequency;
}

void setSampleInterval(Sampler* sampler, double sampleStartTime, double sampleFinishTime)
{
	sampler->sampleStartTime = sampleStartTime;
	sampler->sampleFinishTime = sampleFinishTime;
}

void setCurrentSampleTime(Sampler* sampler, double currentTime)
{
	sampler->currentTime = currentTime;
}

Frame* fillFrame(Sampler* sampler, Frame* frame)
{

	for (uint32_t i = 0; i < frame->size
			&& sampler->currentTime <= sampler->sampleFinishTime; i++) {

		double value = getNextSample(sampler);
		writeFrameDataSample(frame, value, i);
	}

	return frame;
}

uint32_t samplesLeft(Sampler* sampler)
{
	return (sampler->sampleFinishTime - sampler->currentTime) / sampler->deltaTime;
}

static double getNextSample(Sampler* sampler)
{
	double value = 0;

	value = waveY(sampler->wave, sampler->currentTime);
	sampler->currentTime += sampler->deltaTime;

	return value;
}

