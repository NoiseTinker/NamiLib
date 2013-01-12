/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __PERIODIC_H__
#define __PERIODIC_H__

typedef struct {
	double (*func)(double);
} Periodic;

double nami_periodic_y(Periodic* pf, double x);

void nami_set_function(Periodic* pf, double (*func)(double));

void nami_add_waypoint(Periodic* pf, double x, double y);

/*
 * Functions map a position 0 <= x <= 2*PI to a value -1 <= y <= 1.
 */

double nami_sine_wave(double x);

double nami_square_wave(double x);

double nami_triangle_wave(double x);

double nami_sawtooth_wave(double x);

#endif
