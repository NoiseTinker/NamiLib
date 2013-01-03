/*  
 * Copyright 2013 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Wave.h"
#include "FrameReader.h"
#include <math.h>

#define FRAME_SIZE 80
#define SAMPLE_RATE 8000

void TestReadSquareWave(CuTest* tc)
{
	Frame frame;
	FrameReader frameReader;
	uint8_t data[FRAME_SIZE] = {0};

	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameReader(&frameReader, "testdata/squarewave_f100Hz_sf8000Hz_uint8.raw");

	while (readFrame(&frameReader, &frame) > 0) {

		CuAssertTrue(tc, data[0] == 255);
		CuAssertTrue(tc, data[40] == 0);
	}

	closeFrameReader(&frameReader);
}
