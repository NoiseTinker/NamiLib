/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "Fft.h"
#include "CuTest.h"
#include <math.h>
#include <stdio.h>

#define FRAME_SIZE 320
#define SAMPLE_RATE 44000
#define TEST_FREQ 2000

void TestFftFlatSignal(CuTest* tc)
{
	Frame frame;
	double flat[FRAME_SIZE] = {0};
	ComplexNumber spectrum[FRAME_SIZE];

	nami_init_frame(&frame, DOUBLE, flat, FRAME_SIZE);
	nami_fft(&frame, spectrum);

	for (int i = 0; i < FRAME_SIZE; i++) {
		CuAssertTrue(tc, spectrum[i].r == 0);
		CuAssertTrue(tc, spectrum[i].i == 0);
	}
}

void TestFftRossetaCode(CuTest* tc)
{
	Frame frame;
	double flat[8] = {1, 1, 1, 1, 0, 0, 0, 0};
	ComplexNumber spectrum[8];

	nami_init_frame(&frame, DOUBLE, flat, 8);
	nami_fft(&frame, spectrum);

	CuAssertTrue(tc, nami_get_absolute(&spectrum[0]) == 4);
	CuAssertTrue(tc, nami_get_absolute(&spectrum[1]) == 0);
	CuAssertTrue(tc, nami_get_absolute(&spectrum[2]) == 0);
	CuAssertTrue(tc, nami_get_absolute(&spectrum[3]) == 0);

	double* data = nami_frame_double(&frame);

	data[0] = 666;
	data[1] = 666;
	data[2] = 666;
	data[3] = 666;
	data[4] = 666;
	data[5] = 666;
	data[6] = 666;
	data[7] = 666;

	nami_ifft(spectrum, &frame);

	CuAssertTrue(tc, data[0] == 1);
	CuAssertTrue(tc, data[1] == 1);
	CuAssertTrue(tc, data[2] == 1);
	CuAssertTrue(tc, data[3] == 1);
	CuAssertTrue(tc, data[4] == 0);
	CuAssertTrue(tc, data[5] == 0);
	CuAssertTrue(tc, data[6] == 0);
	CuAssertTrue(tc, data[7] == 0);
}
