/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Periodic.h"
#include <math.h>
#include <stdio.h>

struct __Periodic
{
	double (*func)(double);
};

double nami_periodic_y(Periodic* pf, double x)
{
	return pf->func(x);
}

void nami_set_function(Periodic* pf, double (*func)(double))
{
	 pf->func = func;
}

void nami_add_waypoint(Periodic* pf, double x, double y)
{
	/* Not yet implemented. */
}

/*
 * Functions map a position 0 <= x <= 2*PI to a value -1 <= y <= 1.
 */

double nami_sine_wave(double x)
{
	return sin(x);
}

double nami_square_wave(double x)
{
	return sin(x) > 0 ? 1 : -1;
}

double nami_triangle_wave(double x)
{
	double x_mod_2pi = fmod(x, 2*M_PI);
	double a = 1/M_PI_2;
	double b = 0;

	if(x_mod_2pi > M_PI_2
		&& x_mod_2pi < 3*M_PI_2) {
		a = -a;
		b = 2;
	} else if(x_mod_2pi >= 3*M_PI_2) {
		b = -4;
	}

	return a*x + b;
}

double nami_sawtooth_wave(double x)
{
	return (fmod(x, 2*M_PI)/M_PI) - 1;
}

