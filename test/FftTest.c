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
	ComplexNumber fCoeffs[FRAME_SIZE];

	nami_init_frame(&frame, DOUBLE, flat, FRAME_SIZE);
	nami_fft(&frame, fCoeffs);

	for (int i = 0; i < FRAME_SIZE; i++) {
		CuAssertTrue(tc, fCoeffs[i].r == 0);
		CuAssertTrue(tc, fCoeffs[i].i == 0);
	}
}


void TestFftTopFrequencyEven(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_freq(200, 10) == 100);
}

void TestFftTopFrequencyOdd(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_freq(200, 11) - 90.909091 < 0.00001);
}

// Remove below? ->

void TestFftRossetaCode(CuTest* tc)
{
	Frame frame;
	double flat[8] = {1, 1, 1, 1, 0, 0, 0, 0};
	ComplexNumber fCoeffs[8];

	nami_init_frame(&frame, DOUBLE, flat, 8);
	nami_fft(&frame, fCoeffs);

	CuAssertTrue(tc, nami_get_absolute(&fCoeffs[0]) == 4);
	CuAssertTrue(tc, nami_get_absolute(&fCoeffs[1]) == 0);
	CuAssertTrue(tc, nami_get_absolute(&fCoeffs[2]) == 0);
	CuAssertTrue(tc, nami_get_absolute(&fCoeffs[3]) == 0);

	double* data = nami_frame_double(&frame);

	data[0] = 666;
	data[1] = 666;
	data[2] = 666;
	data[3] = 666;
	data[4] = 666;
	data[5] = 666;
	data[6] = 666;
	data[7] = 666;

	nami_ifft(fCoeffs, &frame);

	CuAssertTrue(tc, data[0] == 1);
	CuAssertTrue(tc, data[1] == 1);
	CuAssertTrue(tc, data[2] == 1);
	CuAssertTrue(tc, data[3] == 1);
	CuAssertTrue(tc, data[4] == 0);
	CuAssertTrue(tc, data[5] == 0);
	CuAssertTrue(tc, data[6] == 0);
	CuAssertTrue(tc, data[7] == 0);
}
