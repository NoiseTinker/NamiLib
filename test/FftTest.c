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

	initFrame(&frame, flat, FRAME_SIZE);
	fft(&frame, spectrum);

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

	initFrame(&frame, flat, 8);
	fft(&frame, spectrum);

	CuAssertTrue(tc, getAbsolute(&spectrum[0]) == 4);
	CuAssertTrue(tc, getAbsolute(&spectrum[1]) == 0);
	CuAssertTrue(tc, getAbsolute(&spectrum[2]) == 0);
	CuAssertTrue(tc, getAbsolute(&spectrum[3]) == 0);

	frame.data[0] = 666;
	frame.data[1] = 666;
	frame.data[2] = 666;
	frame.data[3] = 666;
	frame.data[4] = 666;
	frame.data[5] = 666;
	frame.data[6] = 666;
	frame.data[7] = 666;

	ifft(spectrum, &frame);

	CuAssertTrue(tc, frame.data[0] == 1);
	CuAssertTrue(tc, frame.data[1] == 1);
	CuAssertTrue(tc, frame.data[2] == 1);
	CuAssertTrue(tc, frame.data[3] == 1);
	CuAssertTrue(tc, frame.data[4] == 0);
	CuAssertTrue(tc, frame.data[5] == 0);
	CuAssertTrue(tc, frame.data[6] == 0);
	CuAssertTrue(tc, frame.data[7] == 0);
}
