/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* A player of PCM frames to default output.
*/

#ifndef __FRAMEPLAYER_H__
#define __FRAMEPLAYER_H__

#include "Frame.h"
#include <stdio.h>
#include <stdbool.h>
#include <portaudio.h>

typedef struct {
	PaStreamParameters outputParameters;
	PaStream *stream;
	bool started;
} FramePlayer;

typedef struct {
	enum FrameEncoding encoding;
	int sample_rate;
	int nbr_channels;
	int frame_size;
} FramePlayerOptions;

FramePlayer* nami_open_player(FramePlayer* frameplayer, FramePlayerOptions options);

bool nami_start_player(FramePlayer* frameplayer);

void nami_close_player(FramePlayer* player);

size_t nami_write_player(FramePlayer* frameplayer, Frame* frame);

/* Can check this before write if need to avoid blocking. */
bool nami_can_write_player(FramePlayer* frameplayer);

#endif
