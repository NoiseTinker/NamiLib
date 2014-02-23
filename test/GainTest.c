/*  
 * Copyright 2014 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "Gain.h"
#include "CuTest.h"
#include <math.h>
#include <stdio.h>

#define FRAME_SIZE 320

void TestGainFactor(CuTest* tc)
{
	CuAssertTrue(tc, nami_gain_factor(0) == 1);
	CuAssertTrue(tc, nami_gain_factor(6) < 2.0 && nami_gain_factor(6) > 1.99);
	CuAssertTrue(tc, nami_gain_factor(12) < 4.0 && nami_gain_factor(12) > 3.98);
}

void TestGainLevel(CuTest* tc)
{
	CuAssertTrue(tc, nami_level_from_uint8(0) <= 0
			&& nami_level_from_uint8(0) > -0.0001);
	CuAssertTrue(tc, nami_level_from_uint8(UINT8_MAX) <= 0
			&& nami_level_from_uint8(UINT8_MAX) > -0.0001);

	CuAssertTrue(tc, nami_level_from_sint16(-INT16_MAX) == 0);
	CuAssertTrue(tc, nami_level_from_sint16(INT16_MAX) == 0);

	CuAssertTrue(tc, nami_level_from_float(-FLT_MAX) == 0);
	CuAssertTrue(tc, nami_level_from_float(FLT_MAX) == 0);

	CuAssertTrue(tc, nami_level_from_double(-DBL_MAX) == 0);
	CuAssertTrue(tc, nami_level_from_double(DBL_MAX) == 0);
}

void TestGainApply(CuTest* tc)
{
	CuAssertTrue(tc, nami_apply_gain_uint8(UINT8_MAX / 2, 10) == UINT8_MAX / 2);
	CuAssertTrue(tc, nami_apply_gain_uint8((UINT8_MAX / 2) + 1, 10) == (UINT8_MAX / 2) + 10);
	CuAssertTrue(tc, nami_apply_gain_uint8((UINT8_MAX / 2) - 1, 10) == (UINT8_MAX / 2) - 10);

	CuAssertTrue(tc, nami_apply_gain_sint16(0, 10) == 0);
	CuAssertTrue(tc, nami_apply_gain_sint16(1, 10) == 10);
	CuAssertTrue(tc, nami_apply_gain_sint16(-1, 10) == -10);

	CuAssertTrue(tc, nami_apply_gain_float(0, 10) == 0);
	CuAssertTrue(tc, nami_apply_gain_float(1, 10) == 10);
	CuAssertTrue(tc, nami_apply_gain_float(-1, 10) == -10);

	CuAssertTrue(tc, nami_apply_gain_double(0, 10) == 0);
	CuAssertTrue(tc, nami_apply_gain_double(1, 10) == 10);
	CuAssertTrue(tc, nami_apply_gain_double(-1, 10) == -10);
}

void TestGainZeroSignal(CuTest* tc)
{
	Frame frame;
	Gain gain;
	GainResult result;
	double zero[FRAME_SIZE] = {0};

	nami_init_frame(&frame, DOUBLE, zero, FRAME_SIZE);
	frame.used = FRAME_SIZE;
	nami_init_gain(&gain);
	nami_apply_gain(&gain, &frame, 10, &result);

	for (int i = 0; i < FRAME_SIZE; i++) {
		CuAssertTrue(tc, zero[i] == 0);
	}

	CuAssertTrue(tc, gain.offset == 0);
	//CuAssertTrue(tc, gain.avg_dBFS <= );
	CuAssertTrue(tc, !result.didClip);
	//CuAssertTrue(tc, result.peak_dBFS <= );
}

void TestGainFlatSignal(CuTest* tc)
{
	Frame frame;
	Gain gain;
	GainResult result;
	double flat[FRAME_SIZE];

	for (int i = 0; i < FRAME_SIZE; i++) {
		flat[i] = 1;
	}

	nami_init_frame(&frame, DOUBLE, flat, FRAME_SIZE);
	frame.used = FRAME_SIZE;
	nami_init_gain(&gain);
	nami_apply_gain(&gain, &frame, 12, &result);

	for (int i = 0; i < FRAME_SIZE; i++) {
		CuAssertTrue(tc, flat[i] < 4
				&& flat[i] > 3.98);
	}
}



