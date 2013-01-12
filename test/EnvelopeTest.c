/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Envelope.h"
#include <math.h>

void TestEnvelope(CuTest* tc)
{
	Envelope env;

	AdsrParameters params;
	params.attack_time = 2;
	params.decay_time = 2;
	params.sustain_level = 0.5;
	params.sustain_time = 2;
	params.release_time = 2;

	nami_set_envelope_function(&env, &nami_adsr, &params);

	CuAssertTrue(tc, nami_envelope_y(&env, 0) == 0);
	CuAssertTrue(tc, nami_envelope_y(&env, 1) == 0.5);
	CuAssertTrue(tc, nami_envelope_y(&env, 2) == 1);
	CuAssertTrue(tc, nami_envelope_y(&env, 3) == 0.75);
	CuAssertTrue(tc, nami_envelope_y(&env, 4) == 0.5);
	CuAssertTrue(tc, nami_envelope_y(&env, 5) == 0.5);
	CuAssertTrue(tc, nami_envelope_y(&env, 6) == 0.5);
	CuAssertTrue(tc, nami_envelope_y(&env, 7) == 0.25);
	CuAssertTrue(tc, nami_envelope_y(&env, 8) == 0);
}

void TestAdsr(CuTest* tc)
{
	AdsrParameters params;
	params.attack_time = 2;
	params.decay_time = 2;
	params.sustain_level = 0.5;
	params.sustain_time = 2;
	params.release_time = 2;

	CuAssertTrue(tc, nami_adsr(0, &params) == 0);
	CuAssertTrue(tc, nami_adsr(1, &params) == 0.5);
	CuAssertTrue(tc, nami_adsr(2, &params) == 1);
	CuAssertTrue(tc, nami_adsr(3, &params) == 0.75);
	CuAssertTrue(tc, nami_adsr(4, &params) == 0.5);
	CuAssertTrue(tc, nami_adsr(5, &params) == 0.5);
	CuAssertTrue(tc, nami_adsr(6, &params) == 0.5);
	CuAssertTrue(tc, nami_adsr(7, &params) == 0.25);
	CuAssertTrue(tc, nami_adsr(8, &params) == 0);
}

void TestRaisedCosine(CuTest* tc)
{
	RaisedCosineParameters params;
	params.rise_time = 1;
	params.fall_time = 1;
	params.sustain_time = 1;

	CuAssertTrue(tc, nami_raised_cosine(-1, &params) == 0);
	CuAssertTrue(tc, nami_raised_cosine(0, &params) == 0);
	CuAssertTrue(tc, fabs(nami_raised_cosine(0.0001, &params) - 0.0001) < 0.0001);
	CuAssertTrue(tc, fabs(nami_raised_cosine(0.5, &params) - 0.5) < 0.0001);
	CuAssertTrue(tc, fabs(nami_raised_cosine(0.9999, &params) - 0.9999) < 0.0001);
	CuAssertTrue(tc, nami_raised_cosine(1.5, &params) == 1);
	CuAssertTrue(tc, fabs(nami_raised_cosine(2.0001, &params) - 0.9999) < 0.0001);
	CuAssertTrue(tc, fabs(nami_raised_cosine(2.5, &params) - 0.5) < 0.0001);
	CuAssertTrue(tc, fabs(nami_raised_cosine(2.9999, &params) - 0.0001) < 0.0001);
	CuAssertTrue(tc, nami_raised_cosine(3, &params) == 0);
	CuAssertTrue(tc, nami_raised_cosine(4, &params) == 0);
}
