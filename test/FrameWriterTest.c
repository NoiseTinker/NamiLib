/*  
 * Copyright 2013 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "CuTest.h"
#include "Wave.h"
#include "Sampler.h"
#include "FrameWriter.h"
#include <math.h>

#define FRAME_SIZE 160
#define SAMPLE_RATE 8000

void TestWriteSineWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter writer;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = nami_angular_frequency_from_frequency(440);

	nami_set_function(&periodic, &nami_sine_wave);
	nami_init_wave(&wave);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_init_sampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/sine_test.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);
}

void TestWriteSquareWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter writer;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = nami_angular_frequency_from_frequency(440);

	nami_set_function(&periodic, &nami_square_wave);
	nami_init_wave(&wave);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_init_sampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/square_test.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);
}

void TestWriteTriangleWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter writer;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = nami_angular_frequency_from_frequency(440);

	nami_set_function(&periodic, &nami_triangle_wave);
	nami_init_wave(&wave);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_init_sampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/triangle_test.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);
}

void TestWriteSawtoothWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter writer;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = nami_angular_frequency_from_frequency(440);

	nami_set_function(&periodic, &nami_sawtooth_wave);
	nami_init_wave(&wave);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_init_sampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/sawtooth_test.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);
}


void TestWriteMorseDit(CuTest* tc)
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
	nami_init_wave(&wave);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_set_envelope(&wave, &envelope);
	nami_init_sampler(&sampler, &wave, 0, 0.080, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/enveloped_sine_test.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);
}

void TestWriteEnvelopedSawtoothWave(CuTest* tc)
{
	Periodic periodic;
	Envelope envelope;
        AdsrParameters params;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter writer;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = nami_angular_frequency_from_frequency(440);

        params.attack_time = 0.020;
        params.decay_time = 0.020;
        params.sustain_time = 1;
	params.sustain_level = 0.5;
	params.release_time = 0.5;

	nami_set_function(&periodic, &nami_sawtooth_wave);
	nami_init_wave(&wave);
	nami_set_envelope_function(&envelope, nami_adsr, (void*)&params);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_set_envelope(&wave, &envelope);
	nami_init_sampler(&sampler, &wave, 0, 1.540, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/enveloped_sawtooth_test.raw");

	while (nami_samples_left(&sampler) > 0) {

		nami_fill_frame(&sampler, &frame);
		nami_write_frame(&writer, &frame);
	}

	nami_close_writer(&writer);
}

void TestWritePSK31Zeros(CuTest* tc)
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

        params.rise_time = 0.016;
        params.fall_time = 0.016;
        params.sustain_time = 0;

	nami_set_function(&periodic, &nami_sine_wave);
	nami_set_envelope_function(&envelope, nami_raised_cosine, (void*)&params);
	nami_init_wave(&wave);
	nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
	nami_set_envelope(&wave, &envelope);
	nami_init_sampler(&sampler, &wave, 0, 0.032, SAMPLE_RATE);
	nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
	nami_open_writer(&writer, "out/test-output/psk31_zeros_test.raw");

	for (int i = 0; i < 40; i++) {

		while (nami_samples_left(&sampler) > 0) {

			nami_fill_frame(&sampler, &frame);
			nami_write_frame(&writer, &frame);
		}

		wave.phase += M_PI;
		nami_set_current_sample_time(&sampler, 0);
	}

	nami_close_writer(&writer);
}

