/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#ifndef __ENVELOPE_H__
#define __ENVELOPE_H__

typedef struct {
	double (*func)(double, void*);
	void* data;
} Envelope;

double nami_envelope_y(Envelope* env, double t);

void nami_set_envelope_function(Envelope* env, double (*func)(double, void*), void*);

/*
 *    /\
 *   /  \______
 *  /          \
 *
 *  A - D - S - R
 *
 *  https://en.wikipedia.org/wiki/Synthesizer#ADSR_envelope
 */
typedef struct {
	double attack_time;
	double decay_time;
	double sustain_level;
	double sustain_time;
	double release_time;
} AdsrParameters;

double nami_adsr(double t, void* data);

/*
 * https://en.wikipedia.org/wiki/Raised-cosine_filter
 */
typedef struct {
	double rise_time;
	double fall_time;
	double sustain_time;
} RaisedCosineParameters;

double nami_raised_cosine(double t, void* data);

#endif
