/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Wave.h"
#include <math.h>
#include <stdio.h>

void TestAddSquareWaveInTime(CuTest* tc)
{
	Periodic periodic;
	Wave wave;

	addFunction(&periodic, &square_wave);
	/* angular velocity = pi */
	addPeriodic(&wave, &periodic, 1, 0, M_PI);

	CuAssertTrue(tc, waveY(&wave, 0) == -1);
	CuAssertTrue(tc, waveY(&wave, 0.01) == 1);
	CuAssertTrue(tc, waveY(&wave, 0.99) == 1);
	CuAssertTrue(tc, waveY(&wave, 1) == 1);
	CuAssertTrue(tc, waveY(&wave, 1.01) == -1);
	CuAssertTrue(tc, waveY(&wave, 1.99) == -1);
	CuAssertTrue(tc, waveY(&wave, 2) == -1);
	CuAssertTrue(tc, waveY(&wave, 3) == 1);
}

void TestAddSquareWaveWithPhase(CuTest* tc)
{
	Periodic periodic;
	Wave wave;

	addFunction(&periodic, &square_wave);
	/* phase = pi, angular velocity = pi */
	addPeriodic(&wave, &periodic, 1, M_PI, M_PI);

	CuAssertTrue(tc, waveY(&wave, 0) == 1);
	CuAssertTrue(tc, waveY(&wave, 0.01) == -1);
	CuAssertTrue(tc, waveY(&wave, 0.99) == -1);
	CuAssertTrue(tc, waveY(&wave, 1) == -1);
	CuAssertTrue(tc, waveY(&wave, 1.01) == 1);
	CuAssertTrue(tc, waveY(&wave, 1.99) == 1);
	CuAssertTrue(tc, waveY(&wave, 2) == 1);
	CuAssertTrue(tc, waveY(&wave, 3) == -1);
}

void TestAddSquareWaveWithAmplitude(CuTest* tc)
{
	Periodic periodic;
	Wave wave;

	addFunction(&periodic, &square_wave);
	/* amplitude = 2, angular velocity = pi */
	addPeriodic(&wave, &periodic, 2, 0, M_PI);

	CuAssertTrue(tc, waveY(&wave, 0) == -2);
	CuAssertTrue(tc, waveY(&wave, 0.01) == 2);
}

