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

#define FRAME_SIZE 4096
#define SAMPLE_RATE 48000

int main() {

	Frame iq_frame;
	Frame audio_frame;
	FrameReader reader;
	FrameReaderOptions reader_options;
	FramePlayer player;
	FramePlayerOptions player_options;
	Gain gain;
	GainResult gainResult;

	reader_options.type = FILE_TYPE;
	reader_options.filename = "../testdata/iq_cf7020kHz_sf48kHz_sint16.raw";

	player_options.encoding = SINT16;
	player_options.sample_rate = SAMPLE_RATE;
	player_options.nbr_channels = 1;
	player_options.frame_size = FRAME_SIZE;

        int16_t data[FRAME_SIZE] = {0};
        nami_init_frame(&iq_frame, SINT16, &data, FRAME_SIZE);

	// TODO: init audio_frame

	nami_init_gain(&gain);
        nami_open_reader(&reader, reader_options);
	nami_open_player(&player, player_options);

	// Loop until done
	while (nami_read_frame(&reader, &iq_frame) > 0) {
		nami_apply_gain(&gain, &iq_frame, 20, &gainResult);
		// Deinterleave
		// Demod
		nami_play_frame(&player, &iq_frame);//play audio frame
	}

	nami_close_player(&player);
	nami_close_reader(&reader);

	return 1;
}
