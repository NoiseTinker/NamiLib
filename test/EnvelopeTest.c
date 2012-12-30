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
	params.attackTime = 2;
	params.decayTime = 2;
	params.sustainLevel = 0.5;
	params.sustainTime = 2;
	params.releaseTime = 2;

	setEnvelopeFunction(&env, &adsr, &params);

	CuAssertTrue(tc, envelopeY(&env, 0) == 0);
	CuAssertTrue(tc, envelopeY(&env, 1) == 0.5);
	CuAssertTrue(tc, envelopeY(&env, 2) == 1);
	CuAssertTrue(tc, envelopeY(&env, 3) == 0.75);
	CuAssertTrue(tc, envelopeY(&env, 4) == 0.5);
	CuAssertTrue(tc, envelopeY(&env, 5) == 0.5);
	CuAssertTrue(tc, envelopeY(&env, 6) == 0.5);
	CuAssertTrue(tc, envelopeY(&env, 7) == 0.25);
	CuAssertTrue(tc, envelopeY(&env, 8) == 0);
}

void TestAdsr(CuTest* tc)
{
	AdsrParameters params;
	params.attackTime = 2;
	params.decayTime = 2;
	params.sustainLevel = 0.5;
	params.sustainTime = 2;
	params.releaseTime = 2;

	CuAssertTrue(tc, adsr(0, &params) == 0);
	CuAssertTrue(tc, adsr(1, &params) == 0.5);
	CuAssertTrue(tc, adsr(2, &params) == 1);
	CuAssertTrue(tc, adsr(3, &params) == 0.75);
	CuAssertTrue(tc, adsr(4, &params) == 0.5);
	CuAssertTrue(tc, adsr(5, &params) == 0.5);
	CuAssertTrue(tc, adsr(6, &params) == 0.5);
	CuAssertTrue(tc, adsr(7, &params) == 0.25);
	CuAssertTrue(tc, adsr(8, &params) == 0);
}

void TestRaisedCosine(CuTest* tc)
{
	RaisedCosineParameters params;
	params.riseTime = 1;
	params.fallTime = 1;
	params.sustainTime = 1;

	CuAssertTrue(tc, raisedCosine(-1, &params) == 0);
	CuAssertTrue(tc, raisedCosine(0, &params) == 0);
	CuAssertTrue(tc, fabs(raisedCosine(0.0001, &params) - 0.0001) < 0.0001);
	CuAssertTrue(tc, fabs(raisedCosine(0.5, &params) - 0.5) < 0.0001);
	CuAssertTrue(tc, fabs(raisedCosine(0.9999, &params) - 0.9999) < 0.0001);
	CuAssertTrue(tc, raisedCosine(1.5, &params) == 1);
	CuAssertTrue(tc, fabs(raisedCosine(2.0001, &params) - 0.9999) < 0.0001);
	CuAssertTrue(tc, fabs(raisedCosine(2.5, &params) - 0.5) < 0.0001);
	CuAssertTrue(tc, fabs(raisedCosine(2.9999, &params) - 0.0001) < 0.0001);
	CuAssertTrue(tc, raisedCosine(3, &params) == 0);
	CuAssertTrue(tc, raisedCosine(4, &params) == 0);
}
