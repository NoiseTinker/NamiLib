/*
* Copyright 2014 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* Demodulator of I/Q signals.
*/

#include "Demodulator.h"

void nami_demod_init(Demodulator* demod, Oscillator* bfo, double (*func)(Oscillator* bfo, double, double))
{
	demod->bfo = bfo;
	demod->func = func;
}

/*
 * 2 * src_frame size = dst_frame size
 */
void nami_demod_frame(Demodulator* demod, Frame* src_frame, Frame* dst_frame)
{
	for (int index = 0; index * 2 < src_frame->used && index < dst_frame->size; index++) {
		double i = nami_frame_read_sample(src_frame, index * 2);
		double q = nami_frame_read_sample(src_frame, (index * 2) + 1);
		nami_frame_write_sample(dst_frame, demod->func(demod->bfo, i, q), index);
	}
}

double nami_demod_usb(Oscillator* bfo, double i, double q)
{
	nami_osc_tick(bfo);
	ComplexNumber bfo_val = nami_osc_cy(bfo);
	return i * nami_get_imaginary(&bfo_val) + q * nami_get_real(&bfo_val);
}

double nami_demod_lsb(Oscillator* bfo, double i, double q)
{
	nami_osc_tick(bfo);
	ComplexNumber bfo_val = nami_osc_cy(bfo);
	return i * nami_get_imaginary(&bfo_val) + q * nami_get_real(&bfo_val);
}

double nami_demod_am(Oscillator* bfo, double i, double q)
{
	ComplexNumber iq;
	iq.r = i;
	iq.i = q;
	return nami_get_absolute(&iq);
}

double nami_demod_fm(Oscillator* bfo, double i, double q)
{
	return 0;
}

