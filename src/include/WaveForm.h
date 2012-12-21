/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*/


void WaveForm* addWave(WaveForm* waveform, Wave* wave);
void WaveForm* multiplicateWave(WaveForm* waveform, Wave* wave);
void WaveForm* removeWave(WaveForm* waveform, Wave* wave);

void WaveForm* setIntervalInSpace(WaveForm* waveform, float t, float x1, float x2);
void WaveForm* setIntervalInTime(WaveForm* waveform, float x, float t1, float t2);

float getTimeInterval(WaveForm* waveform);
float getSpaceInterval(WaveForm* waveform);

float y(WaveForm* waveform, float x);
float y(WaveForm* waveform, float t);

void clear();
