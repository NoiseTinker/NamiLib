/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Envelope.h"

void TestEnvelope(CuTest* tc)
{
	Envelope env;

	AdsrParamters params;
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
	AdsrParamters params;
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
