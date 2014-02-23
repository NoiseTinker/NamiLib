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
	FramePlayer player;
	FramePlayerOptions options;
	Gain gain;
	GainResult gainResult;

	options.encoding = SINT16;
	options.sample_rate = SAMPLE_RATE;
	options.nbr_channels = 1;
	options.frame_size = FRAME_SIZE;

        int16_t data[FRAME_SIZE] = {0};

        nami_init_frame(&iq_frame, SINT16, &data, FRAME_SIZE);
	nami_init_gain(&gain);
	// TODO: init audio_frame
        nami_open_reader(&reader, "../testdata/iq_cf7020kHz_sf48kHz_sint16.raw");
	nami_open_player(&player, options);

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
