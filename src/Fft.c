/*
* Copyright 2012 Daniel Hjort. All rights reserved.
* Author: Daniel Hjort
*
* The parameter f_coefs needs to point to an array of
* ComplexNumber with same number of elements as the
* frame size and also be 2^n.
*/

#include <math.h>
#include <assert.h>
#include "Fft.h"

extern void cdft(int, int, double *, int *, double *);
static void nami_copy_to_coeffs();
static void nami_copy_to_frame();

void nami_fft(Frame* frame, ComplexNumber* f_coefs)
{
	size_t frame_size = nami_frame_size(frame);
	int ip[2 + (int)(sqrt(frame_size + 0.5) / 2)]; // Work area for bit reversal
	double w[frame_size / 2]; // Cos/Sin table
	ip[0] = 0;

	assert(sizeof(ComplexNumber) * 2 == sizeof(double) * 4);
	assert(frame->encoding == DOUBLE);

	nami_copy_to_coeffs(frame, f_coefs);

	// Call Ooura Complex Discrete Fourier Transform
	cdft(frame_size, 1, (double*)f_coefs, ip, w);
}

void nami_ifft(ComplexNumber* f_coefs, Frame* frame)
{
	size_t frame_size = nami_frame_size(frame);
	int ip[2 + (int)(sqrt(frame_size + 0.5) / 2)]; // Work area for bit reversal
	double w[frame_size / 2]; // Cos/Sin table
	ip[0] = 0;

	assert(sizeof(ComplexNumber) * 2 == sizeof(double) * 4);
	assert(frame->encoding == DOUBLE);

	// Call Ooura Complex Discrete Fourier Transform
	cdft(frame_size, -1, (double*)f_coefs, ip, w);

	//for (int j = 0; j <= nami_frame_size(frame) - 1; j++) {
	//	f_coefs[j].r *= 1.0 / numFrequencies;
	//} // Need ont the inverse also?

	nami_copy_to_frame(f_coefs, frame);
}

static void nami_copy_to_coeffs(Frame* frame, ComplexNumber* f_coefs)
{
	size_t size = nami_frame_size(frame);
	double* data = nami_frame_double(frame);

	for (size_t i = 0; i < size; i++) {
		f_coefs[i].r = data[i];
		f_coefs[i].i = 0;
	}
}

static void nami_copy_to_frame(ComplexNumber* f_coefs, Frame* frame)
{
	size_t size = nami_frame_size(frame);
	double* data = nami_frame_double(frame);

	for (size_t i = 0; i < size; i++) {
		data[i] = f_coefs[i].r;
	}
}

PowerSpectrum* nami_init_spectrum(PowerSpectrum* spectrum, SpectrumFreqency* freqs, ComplexNumber* f_coefs, uint32_t sampling_frequency, size_t nbr_samples)
{
	spectrum->freqs = freqs;
	spectrum->f_coefs = f_coefs;
	spectrum->sampling_frequency = sampling_frequency;
	spectrum->nbr_samples = nbr_samples;

	// Calculate top frequency
	double top_freq = nami_fft_top_freq(sampling_frequency, nbr_samples);

	// Calculate number of frequencies in result
	int nbr_freqs = nami_fft_top_index(nbr_samples) + 1; // TODO: Top index better? Avoids +1 then -1

    for (int i = 0; i < nbr_freqs; i++) {
		
		// Set frequency
		freqs[i].freq = (double)i * (top_freq / (nbr_freqs - 1));
		assert(freqs[i].freq <= top_freq);
		
		// Normalise
		// Divide by nbr samples
		double real = f_coefs[i].r / nbr_samples;
		double imaginary = f_coefs[i].r / nbr_samples;

		// Calculate amplitude
		int is_dc_or_nyquist = (i == 0 || i == (nbr_freqs - 1));
		double scaling_factor = is_dc_or_nyquist ? 1.0 : 2.0; // Excluding DC and Nyquist
		freqs[i].amplitude = scaling_factor * sqrt(real * real + imaginary * imaginary); // 2x since amplitude split between positive and negative frequencies
	
		// Calculate phase
		freqs[i].phase = atan2(imaginary, real);
	}

	return spectrum;
}

double nami_fft_top_freq(uint32_t sampling_frequency, size_t nbr_samples)
{
	double correction = nbr_samples % 2 == 0 ? 1 : ((double)nbr_samples - 1) / nbr_samples;
	return (sampling_frequency / 2) * correction;
}

size_t nami_fft_top_index(size_t nbr_samples)
{
	uint16_t nbr_freqs = (nbr_samples / 2) + 1; // floor(n/2) + 1(DC)
	return nbr_freqs - 1;
}

double nami_freq_at_index(int index) {
	// TODO
	return 0;
}
