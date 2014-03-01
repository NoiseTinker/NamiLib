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
	FrameReader reader;
	FrameReaderOptions options;
	uint8_t data[FRAME_SIZE] = {0};

	options.type = FILE_TYPE;
	options.filename = "testdata/squarewave_f100Hz_sf8000Hz_uint8.raw";

	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_reader(&reader, options);

	while (nami_read_frame(&reader, &frame) > 0) {

		CuAssertTrue(tc, data[0] == 255);
		CuAssertTrue(tc, data[40] == 0);
	}

	nami_close_reader(&reader);
}
