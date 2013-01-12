/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Periodic.h"
#include <math.h>
#include <stdio.h>

void TestSine(CuTest* tc)
{
	CuAssertTrue(tc, nami_sine_wave(0) == 0);
	CuAssertTrue(tc, nami_sine_wave(M_PI/2) == 1);
	CuAssertTrue(tc, nami_sine_wave((3*M_PI)/2) == -1);
}

void TestSquare(CuTest* tc)
{
	CuAssertTrue(tc, nami_square_wave(0) == -1);
	CuAssertTrue(tc, nami_square_wave(0.01) == 1);
	CuAssertTrue(tc, nami_square_wave(M_PI-0.01) == 1);
	CuAssertTrue(tc, nami_square_wave(M_PI+0.01) == -1);
	CuAssertTrue(tc, nami_square_wave(2*M_PI-0.01) == -1);
	CuAssertTrue(tc, nami_square_wave(2*M_PI+0.01) == 1);
}

void TestTriangle(CuTest* tc)
{
	CuAssertTrue(tc, nami_triangle_wave(0) == 0);
	CuAssertTrue(tc, nami_triangle_wave(M_PI_4) == 0.5);
	CuAssertTrue(tc, nami_triangle_wave(M_PI_2) == 1);
	CuAssertTrue(tc, nami_triangle_wave(3*M_PI_4) == 0.5);
	CuAssertTrue(tc, nami_triangle_wave(M_PI) == 0);
	CuAssertTrue(tc, nami_triangle_wave(M_PI+M_PI_4) == -0.5);
	CuAssertTrue(tc, nami_triangle_wave(3*M_PI_2) == -1);
	CuAssertTrue(tc, nami_triangle_wave(2*M_PI-M_PI_4) == -0.5);
	CuAssertTrue(tc, fabs(nami_triangle_wave(2*M_PI-0.01)) < 0.01);
}

void TestSawtooth(CuTest* tc)
{
	CuAssertTrue(tc, nami_sawtooth_wave(0) == -1);
	CuAssertTrue(tc, nami_sawtooth_wave(M_PI) == 0);
	CuAssertTrue(tc, fabs(nami_sawtooth_wave(2*M_PI-0.01)-1) < 0.01);
	CuAssertTrue(tc, nami_sawtooth_wave(2*M_PI) == -1);
	CuAssertTrue(tc, nami_sawtooth_wave(3*M_PI) == 0);
}

void TestAddFunction(CuTest* tc)
{
	Periodic periodic;
	nami_set_function(&periodic, &nami_sine_wave);

	CuAssertTrue(tc, nami_periodic_y(&periodic, 0) == 0);
	CuAssertTrue(tc, nami_periodic_y(&periodic, M_PI/2) == 1);
}

void TestAddWayPoints(CuTest* tc)
{
	/* Not yet implemented. */
	CuAssertTrue(tc, 0 == 0);
}
