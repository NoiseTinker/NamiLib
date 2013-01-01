/*  
 * Copyright 2013 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Wave.h"
#include "Sampler.h"

#define FRAME_SIZE 10
#define SAMPLE_RATE 10

void TestSampleSquareWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(4);

	setFunction(&periodic, &square_wave);
	setPeriodic(&wave, &periodic, 1, 0, angularFrequency);
	initSampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);

		CuAssertTrue(tc, data[0] == 0);
		CuAssertTrue(tc, data[1] == 255);
		CuAssertTrue(tc, data[2] == 0);
	}
}

