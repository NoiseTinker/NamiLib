/*
* Copyright 2014 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* Reads IQ data from socket (rtl_tcp) and demodulates it before playing.
*/

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "Frame.h"
#include "FrameRecorder.h"
#include "FramePlayer.h"
#include "Gain.h"

#define IQ_FRAME_SIZE 200000
#define AUDIO_FRAME_SIZE 4096
#define AUDIO_SAMPLE_RATE 48000

int main() {

	Frame iq_frame;
	Frame audio_frame;

	FrameRecorder recorder;
	FrameRecorderOptions recorder_options;
	FramePlayer player;
	FramePlayerOptions player_options;

	struct sockaddr_in stSockAddr;
	int socket_result;
	recorder_options.socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (-1 == recorder_options.socket_fd)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}

	memset(&stSockAddr, 0, sizeof(stSockAddr));

	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(1234);
	socket_result = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);

	if (0 > socket_result) {
		perror("error: first parameter is not a valid address family");
		close(recorder_options.socket_fd);
		exit(EXIT_FAILURE);
	} else if (0 == socket_result) {
		perror("char string (second parameter does not contain valid ipaddress)");
		close(recorder_options.socket_fd);
		exit(EXIT_FAILURE);
	}

	if (-1 == connect(recorder_options.socket_fd, (struct sockaddr *)&stSockAddr, sizeof(stSockAddr))) {
		perror("connect failed");
		close(recorder_options.socket_fd);
		exit(EXIT_FAILURE);
	}

	recorder_options.type = SOCKET;

	player_options.encoding = SINT16;
	player_options.sample_rate = AUDIO_SAMPLE_RATE;
	player_options.nbr_channels = 1;
	player_options.frame_size = AUDIO_FRAME_SIZE;

        uint8_t iq_data[IQ_FRAME_SIZE] = {0};
        nami_init_frame(&iq_frame, UINT8, &iq_data, IQ_FRAME_SIZE);

	uint8_t audio_data[IQ_FRAME_SIZE] = {0};
        nami_init_frame(&iq_frame, SINT16, &audio_data, AUDIO_FRAME_SIZE);

        nami_open_recorder(&recorder, recorder_options);
	//nami_open_player(&player, player_options);

	int loops = 0;

	// Loop until done
	while (nami_record_frame(&recorder, &iq_frame) > 0
		&& loops < 1000) {
		// Deinterleave
		// Demod
		printf("[%d %d]", loops, iq_data[0]);
		// Down sample
		//nami_play_frame(&player, &iq_frame); //play audio frame

		loops++;
	}

	//nami_close_player(&player);
	nami_close_recorder(&recorder);

	return 1;
}
