/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __PERIODIC_H__
#define __PERIODIC_H__

typedef struct {
	double (*func)(double);
} Periodic;

double y(Periodic* pf, double x);

void addFunction(Periodic* pf, double (*func)(double));

void addWayPoint(Periodic* pf, double x, double y);

void clear(Periodic* pf);

/*
 * Functions map a position 0 <= x <= 2*PI to a value -1 <= y <= 1.
 */

double sine_wave(double x);

double square_wave(double x);

double triangle_wave(double x);

double sawtooth_wave(double x);

#endif
