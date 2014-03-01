/*
* Copyright 2014 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/

#include "FrameRecorder.h"

bool nami_open_recorder(FrameRecorder* recorder, FrameRecorderOptions options)
{
	return true;
}

void nami_close_recorder(FrameRecorder* recorder)
{

}

bool nami_recorder_available(FrameRecorder* recorder)
{
	return false;
}

size_t nami_record_frame(FrameRecorder* recorder, Frame* frame)
{
	return 0;
}
