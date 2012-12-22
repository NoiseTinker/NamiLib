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
	CuAssertTrue(tc, sine_wave(0) == 0);
	CuAssertTrue(tc, sine_wave(M_PI/2) == 1);
	CuAssertTrue(tc, sine_wave((3*M_PI)/2) == -1);
}

void TestSquare(CuTest* tc)
{
	CuAssertTrue(tc, square_wave(0) == -1);
	CuAssertTrue(tc, square_wave(0.01) == 1);
	CuAssertTrue(tc, square_wave(M_PI-0.01) == 1);
	CuAssertTrue(tc, square_wave(M_PI+0.01) == -1);
	CuAssertTrue(tc, square_wave(2*M_PI-0.01) == -1);
	CuAssertTrue(tc, square_wave(2*M_PI+0.01) == 1);
}

void TestTriangle(CuTest* tc)
{
	CuAssertTrue(tc, triangle_wave(0) == 0);
	CuAssertTrue(tc, triangle_wave(M_PI_4) == 0.5);
	CuAssertTrue(tc, triangle_wave(M_PI_2) == 1);
	CuAssertTrue(tc, triangle_wave(3*M_PI_4) == 0.5);
	CuAssertTrue(tc, triangle_wave(M_PI) == 0);
	CuAssertTrue(tc, triangle_wave(M_PI+M_PI_4) == -0.5);
	CuAssertTrue(tc, triangle_wave(3*M_PI_2) == -1);
	CuAssertTrue(tc, triangle_wave(2*M_PI-M_PI_4) == -0.5);
	CuAssertTrue(tc, fabs(triangle_wave(2*M_PI-0.01)) < 0.01);
}

void TestSawtooth(CuTest* tc)
{
	CuAssertTrue(tc, sawtooth_wave(0) == -1);
	CuAssertTrue(tc, sawtooth_wave(M_PI) == 0);
	CuAssertTrue(tc, fabs(sawtooth_wave(2*M_PI-0.01)-1) < 0.01);
	CuAssertTrue(tc, sawtooth_wave(2*M_PI) == -1);
	CuAssertTrue(tc, sawtooth_wave(3*M_PI) == 0);
}

void TestAddFunction(CuTest* tc)
{
	Periodic periodic;
	addFunction(&periodic, &sine_wave);

	CuAssertTrue(tc, y(&periodic, 0) == 0);
	CuAssertTrue(tc, y(&periodic, M_PI/2) == 1);
}

void TestAddWayPoints(CuTest* tc)
{
	/* Not yet implemented. */
	CuAssertTrue(tc, 0 == 0);
}

void TestClear(CuTest* tc)
{
	Periodic periodic;
	addFunction(&periodic, (double (*)(double))123);

	CuAssertTrue(tc, periodic.func == (double (*)(double))123);

	clear(&periodic);

	CuAssertTrue(tc, periodic.func == NULL);
}

