/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

float y(Wave* wave, float x, float t);

void addPeriodic(Wave* wave, Periodic* func,
	float amplitude, float phase, float frequency);

void clear();
