/*
* Copyright 2013 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "FramePlayer.h"

#define PA_SAMPLE_TYPE paInt16

void handle_error(FramePlayer* frameplayer, PaError err);

PaSampleFormat frame_encoding_to_pa_sampleformat(enum FrameEncoding encoding);

FramePlayer* nami_open_player(FramePlayer* frameplayer, FramePlayerOptions options)
{
	PaError err;

	PaSampleFormat sampleformat =  frame_encoding_to_pa_sampleformat(options.encoding);

	err = Pa_Initialize(); // Move to AudioContext?

	if( err != paNoError ) {
		handle_error(frameplayer, err);
		return NULL;
	}

	frameplayer->outputParameters.device = Pa_GetDefaultOutputDevice();

	printf( "Output device # %d.\n", frameplayer->outputParameters.device);
	printf( "Output LL: %g s\n", Pa_GetDeviceInfo(frameplayer->outputParameters.device)->defaultLowOutputLatency);
	printf( "Output HL: %g s\n", Pa_GetDeviceInfo(frameplayer->outputParameters.device)->defaultHighOutputLatency);

        frameplayer->outputParameters.channelCount = options.nbr_channels;
        frameplayer->outputParameters.sampleFormat = sampleformat;
        frameplayer->outputParameters.suggestedLatency = Pa_GetDeviceInfo(frameplayer->outputParameters.device )->defaultHighOutputLatency;
        frameplayer->outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(
		&frameplayer->stream,
		NULL, // No input
		&frameplayer->outputParameters,
		options.sample_rate,
		options.frame_size,
		paClipOff, /* we won't output out of range samples so don't bother clipping them */
		NULL, /* no callback, use blocking API */
		NULL ); /* no callback, so no callback userData */

	if( err != paNoError ) {
		handle_error(frameplayer, err);
		return NULL;
	}

	frameplayer->started = false;

	return frameplayer;
}

bool nami_start_player(FramePlayer* frameplayer)
{
	bool result = true;
	PaError err;
	err = Pa_StartStream(frameplayer->stream);

	if( err != paNoError ) {
		handle_error(frameplayer, err);
		result = false;
	}
	return result;
}


void nami_close_player(FramePlayer* frameplayer)
{
	PaError err;
	err = Pa_StopStream(frameplayer->stream);

	if( err != paNoError ) {
		handle_error(frameplayer, err);
	}

	Pa_Terminate(); // Move to AudioContext?
}

size_t nami_play_frame(FramePlayer* frameplayer, Frame* frame)
{
	PaError err;

	if (!frameplayer->started) {
		frameplayer->started = nami_start_player(frameplayer);
	}

	err = Pa_WriteStream(frameplayer->stream, frame->data, frame->used);

	if( err != paNoError ) {
		handle_error(frameplayer, err);
	}

	return 0;
}

bool nami_can_play_frame(FramePlayer* frameplayer)
{
	return true; // TODO: check via stream API
}

void handle_error(FramePlayer* frameplayer, PaError err) {

	if(frameplayer->stream) {
		Pa_AbortStream(frameplayer->stream);
		Pa_CloseStream(frameplayer->stream);
	}
	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n" );
	fprintf(stderr, "Error number: %d\n", err );
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
}

PaSampleFormat frame_encoding_to_pa_sampleformat(enum FrameEncoding encoding)
{
	PaSampleFormat format = -1;

	switch (encoding)
	{
		case UINT8:
			format = paUInt8;
			break;
		case SINT16:
			format = paInt16;
			break;
		case FLOAT:
			format = paFloat32;
			break;
		case DOUBLE:
		default:
			fprintf(stderr, "Encoding not supported.\n");
			break;
	}

	return format;
}
