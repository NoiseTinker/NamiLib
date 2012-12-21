/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

float y(Periodic* func, float x);

void addFunction(Periodic* func, float (*func)(float));
void addWayPoint(Periodic* func, float x, float y);

void clear();

/*
 * Functions map a position 0 <= x <= 1 to a value -1 <= y <= 1.
 */

float sine_wave(float x);

float square_wave(float x);

float triangle_wave(float x);

float sawtooth_wave(float x);
