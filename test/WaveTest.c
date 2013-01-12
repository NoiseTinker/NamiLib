/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Wave.h"
#include <math.h>
#include <stdio.h>

void TestSetSquareWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;

	nami_set_function(&periodic, &nami_square_wave);
	/* angular velocity = pi */
	nami_set_periodic(&wave, &periodic, 1, 0, M_PI);

	CuAssertTrue(tc, nami_wave_y(&wave, 0) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 0.01) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 0.99) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 1) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 1.01) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 1.99) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 2) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 3) == 1);
}

void TestSetSquareWaveWithPhase(CuTest* tc)
{
	Periodic periodic;
	Wave wave;

	nami_set_function(&periodic, &nami_square_wave);
	/* phase = pi, angular velocity = pi */
	nami_set_periodic(&wave, &periodic, 1, M_PI, M_PI);

	CuAssertTrue(tc, nami_wave_y(&wave, 0) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 0.01) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 0.99) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 1) == -1);
	CuAssertTrue(tc, nami_wave_y(&wave, 1.01) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 1.99) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 2) == 1);
	CuAssertTrue(tc, nami_wave_y(&wave, 3) == -1);
}

void TestSetSquareWaveWithAmplitude(CuTest* tc)
{
	Periodic periodic;
	Wave wave;

	nami_set_function(&periodic, &nami_square_wave);
	/* amplitude = 2, angular velocity = pi */
	nami_set_periodic(&wave, &periodic, 2, 0, M_PI);

	CuAssertTrue(tc, nami_wave_y(&wave, 0) == -2);
	CuAssertTrue(tc, nami_wave_y(&wave, 0.01) == 2);
}

void TestAngularFrequencyFromFrequency(CuTest* tc)
{
	CuAssertTrue(tc, nami_angular_frequency_from_frequency(440) == 2*M_PI*440);
}

void TestAngularFrequencyFromPeriod(CuTest* tc)
{
	CuAssertTrue(tc, nami_angular_frequency_from_period(0.00227) == (2*M_PI)/0.00227);
}

