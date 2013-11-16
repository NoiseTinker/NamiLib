/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "Wave.h"
#include "Sampler.h"
#include "FrameWriter.h"

#define FRAME_SIZE 160
#define SAMPLE_RATE 8000

int main()
{
	Periodic periodic;
	Envelope envelope;
        RaisedCosineParameters params;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter writer;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = nami_angular_frequency_from_frequency(700);

        params.rise_time = 0.020;
        params.fall_time = 0.020;
        params.sustain_time = 0.040;

	nami_set_function(&periodic, &nami_sine_wave);
	nami_set_envelope_function(&envelope, nami_raised_cosine, (void*)&params);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_set_envelope(&wave, &envelope);
	nami_init_sampler(&sampler, &wave, 0, 0.080, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "morse_dit.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);

	return 1;
}
