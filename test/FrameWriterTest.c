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
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(440);

	setFunction(&periodic, &sine_wave);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	initSampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/sine_test.raw");

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);
		writeFrame(&frameWriter, &frame);
	}

	closeFrameWriter(&frameWriter);
}

void TestWriteSquareWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(440);

	setFunction(&periodic, &square_wave);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	initSampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/square_test.raw");

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);
		writeFrame(&frameWriter, &frame);
	}

	closeFrameWriter(&frameWriter);
}

void TestWriteTriangleWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(440);

	setFunction(&periodic, &triangle_wave);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	initSampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/triangle_test.raw");

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);
		writeFrame(&frameWriter, &frame);
	}

	closeFrameWriter(&frameWriter);
}

void TestWriteSawtoothWave(CuTest* tc)
{
	Periodic periodic;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(440);

	setFunction(&periodic, &sawtooth_wave);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	initSampler(&sampler, &wave, 0, 2, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/sawtooth_test.raw");

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);
		writeFrame(&frameWriter, &frame);
	}

	closeFrameWriter(&frameWriter);
}


void TestWriteEnvelopedSineWave(CuTest* tc)
{
	Periodic periodic;
	Envelope envelope;
        RaisedCosineParameters params;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(440);

        params.riseTime = 0.020;
        params.fallTime = 0.020;
        params.sustainTime = 1;

	setFunction(&periodic, &sine_wave);
	setEnvelopeFunction(&envelope, raisedCosine, (void*)&params);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	setEnvelope(&wave, &envelope);
	initSampler(&sampler, &wave, 0, 1.040, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/enveloped_sine_test.raw");

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);
		writeFrame(&frameWriter, &frame);
	}

	closeFrameWriter(&frameWriter);
}

void TestWriteEnvelopedSawtoothWave(CuTest* tc)
{
	Periodic periodic;
	Envelope envelope;
        AdsrParameters params;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(440);

        params.attackTime = 0.020;
        params.decayTime = 0.020;
        params.sustainTime = 1;
	params.sustainLevel = 0.5;
	params.releaseTime = 0.5;

	setFunction(&periodic, &sawtooth_wave);
	setEnvelopeFunction(&envelope, adsr, (void*)&params);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	setEnvelope(&wave, &envelope);
	initSampler(&sampler, &wave, 0, 1.540, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/enveloped_sawtooth_test.raw");

	while (samplesLeft(&sampler) > 0) {

		fillFrame(&sampler, &frame);
		writeFrame(&frameWriter, &frame);
	}

	closeFrameWriter(&frameWriter);
}

void TestWritePSK31Zeros(CuTest* tc)
{
	Periodic periodic;
	Envelope envelope;
        RaisedCosineParameters params;
	Wave wave;
	Sampler sampler;
	Frame frame;
	FrameWriter frameWriter;
	uint8_t data[FRAME_SIZE] = {0};
	double angularFrequency = angularFrequencyFromFrequency(700);

        params.riseTime = 0.020;
        params.fallTime = 0.020;
        params.sustainTime = 0;

	setFunction(&periodic, &sine_wave);
	setEnvelopeFunction(&envelope, raisedCosine, (void*)&params);
	setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
	setEnvelope(&wave, &envelope);
	initSampler(&sampler, &wave, 0, 0.040, SAMPLE_RATE);
	initFrame(&frame, UINT8, &data, FRAME_SIZE);
	openFrameWriter(&frameWriter, "out/test-output/psk31_zeros_test.raw");

	for (int i = 0; i < 40; i++) {

		while (samplesLeft(&sampler) > 0) {

			fillFrame(&sampler, &frame);
			writeFrame(&frameWriter, &frame);
		}

		wave.phase += M_PI;
		setCurrentSampleTime(&sampler, 0);
	}

	closeFrameWriter(&frameWriter);
}

