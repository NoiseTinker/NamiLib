/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* Reads a raw audio file containing IQ data and demodulates it before playing.
*/

#include "Frame.h"
#include "FrameReader.h"
#include "FramePlayer.h"
#include "Gain.h"
#include "Wave.h"
#include "Oscillator.h"
#include "Demodulator.h"

#define AUDIO_FRAME_SIZE 2048
#define IQ_FRAME_SIZE 2 * AUDIO_FRAME_SIZE
#define SAMPLE_RATE 48000
#define BFO_FREQ 5400

int main() {

	Frame iq_frame;
	Frame audio_frame;
	FrameReader reader;
	FrameReaderOptions reader_options;
	FramePlayer player;
	FramePlayerOptions player_options;
	Gain gain;
	GainResult gainResult;
	Oscillator bfo;
	Demodulator demod;

	reader_options.type = FILE_TYPE;
	reader_options.filename = "../testdata/iq_cf14181kHz_sf48kHz_sint16.raw";

	player_options.encoding = SINT16;
	player_options.sample_rate = SAMPLE_RATE;
	player_options.nbr_channels = 1;
	player_options.frame_size = AUDIO_FRAME_SIZE;

    int16_t iq_data[IQ_FRAME_SIZE] = {0};
    nami_init_frame(&iq_frame, SINT16, &iq_data, IQ_FRAME_SIZE);
	int16_t audio_data[AUDIO_FRAME_SIZE] = {0};
    nami_init_frame(&audio_frame, SINT16, &audio_data, AUDIO_FRAME_SIZE);

	nami_init_gain(&gain);
	nami_osc_init(&bfo, nami_angular_frequency_from_frequency(BFO_FREQ), SAMPLE_RATE);
	nami_demod_init(&demod, &bfo, &nami_demod_usb);

    nami_open_reader(&reader, reader_options);
	nami_open_player(&player, player_options);

	// Loop until done
	while (nami_read_frame(&reader, &iq_frame) > 0) {

		nami_apply_gain(&gain, &iq_frame, 30, &gainResult);
		nami_demod_frame(&demod, &iq_frame, &audio_frame);
		nami_play_frame(&player, &audio_frame);
	}

	nami_close_player(&player);
	nami_close_reader(&reader);

	return 1;
}
