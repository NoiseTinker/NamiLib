/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Oscillator.h"
#include <math.h>
#include <stdlib.h>

void TestInitAndTick(CuTest* tc)
{
	Oscillator osc;

	nami_osc_init(&osc, 2*M_PI, 4);

	CuAssertTrue(tc, osc.angular_frequency == 2*M_PI);
	CuAssertTrue(tc, osc.delta_time == 1.0/4);
	CuAssertTrue(tc, osc.current_time == 0);

	nami_osc_tick(&osc);

	CuAssertTrue(tc, osc.current_time == 0.25);

	nami_osc_tick(&osc);
	nami_osc_tick(&osc);
	nami_osc_tick(&osc);

	CuAssertTrue(tc, osc.current_time == 1);

	nami_osc_tick(&osc);

	CuAssertTrue(tc, osc.current_time == 0.25);
}

void TestRealAndImg(CuTest* tc)
{
	Oscillator osc;
	ComplexNumber cn;

	nami_osc_init(&osc, 2*M_PI, 4);

	CuAssertTrue(tc, nami_osc_y(&osc) == 1);
	cn = nami_osc_cy(&osc);
	CuAssertTrue(tc, cn.r == 1);
	CuAssertTrue(tc, cn.i == 0);

	nami_osc_tick(&osc);
	cn = nami_osc_cy(&osc);
	CuAssertTrue(tc, fabs(cn.r - 0) < 0.0001);
	CuAssertTrue(tc, fabs(cn.i - 1) < 0.0001);

	nami_osc_tick(&osc);
	cn = nami_osc_cy(&osc);
	CuAssertTrue(tc, fabs(cn.r - (-1)) < 0.0001);
	CuAssertTrue(tc, fabs(cn.i - 0) < 0.0001);

	nami_osc_tick(&osc);
	cn = nami_osc_cy(&osc);
	CuAssertTrue(tc, fabs(cn.r - 0) < 0.0001);
	CuAssertTrue(tc, fabs(cn.i - (-1)) < 0.0001);

	nami_osc_tick(&osc);
	cn = nami_osc_cy(&osc);
	CuAssertTrue(tc, fabs(cn.r - 1) < 0.0001);
	CuAssertTrue(tc, fabs(cn.i - 0) < 0.0001);
}
