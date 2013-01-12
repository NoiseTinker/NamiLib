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
	double angularFrequency = nami_angular_frequency_from_frequency(4);

	nami_set_function(&periodic, &nami_square_wave);
	nami_set_periodic(&wave, &periodic, 1, 0, angularFrequency);
	nami_init_sampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);

		CuAssertTrue(tc, data[0] == 0);
		CuAssertTrue(tc, data[1] == 255);
		CuAssertTrue(tc, data[2] == 0);
	}
}

