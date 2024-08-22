/*  
 * Copyright 2012 Daniel Hjort. All rights reserved.
 * Author: Daniel Hjort
 */

#include "Fft.h"
#include "CuTest.h"
#include <math.h>
#include <stdio.h>

extern void cdft(int, int, double *, int *, double *);

#define FRAME_SIZE 2048
#define SAMPLE_RATE 1000
#define TEST_FREQ1 220
#define TEST_FREQ2 440
#define TEST_AMPL1 3.0
#define TEST_AMPL2 5.0
#define TEST_DC_OFFSET 2.0


void TestFftFlatSignal(CuTest* tc)
{
	Frame frame;
	double flat[FRAME_SIZE];
	ComplexNumber f_coefs[FRAME_SIZE];

	for (int i = 0; i < FRAME_SIZE; i++) {
	    flat[i] = 0;
	}

	nami_init_frame(&frame, DOUBLE, flat, FRAME_SIZE);
	nami_fft(&frame, f_coefs);

	for (int i = 0; i < FRAME_SIZE; i++) {
		CuAssertTrue(tc, f_coefs[i].r == 0);
		CuAssertTrue(tc, f_coefs[i].i == 0);
	}
}

void TestFftDCSignal(CuTest* tc)
{
	Frame frame;
	double flat[FRAME_SIZE];
	ComplexNumber f_coefs[FRAME_SIZE];
	SpectrumFreqency freqs[nami_fft_top_index(FRAME_SIZE) + 1];
	PowerSpectrum spectrum;
	
	for (int i = 0; i < FRAME_SIZE; i++) {
	    flat[i] = 0.5;
	}

	nami_init_frame(&frame, DOUBLE, flat, FRAME_SIZE);
	nami_fft(&frame, f_coefs);

	nami_init_spectrum(&spectrum, freqs, f_coefs, SAMPLE_RATE, FRAME_SIZE);

	CuAssertTrue(tc, freqs[0].amplitude - 0.5 < 0.15); // Ideally == 0.5, scalloping loss
	CuAssertTrue(tc, freqs[1].amplitude == 0);
	CuAssertTrue(tc, freqs[100].amplitude == 0);
}

void TestFftTwoSinesSignal(CuTest* tc) {	
	// TODO
}

void TestInverseFft(CuTest* tc) {	
	// TODO
}

void TestFftTopFrequencyEven(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_freq(200, 10) == 100);
}

void TestFftTopFrequencyOdd(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_freq(200, 11) - 90.909091 < 0.00001);
}

void TestFftTopFrequencyOddManySamples(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_freq(200, 10000) - 100 < 0.00001);
}

void TestFftTopIndexEven(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_index(10) == 5);
}

void TestFftTopIndexOdd(CuTest* tc)
{
	CuAssertTrue(tc, nami_fft_top_index(11) == 5);
}

void TestFreqAtIndex(CuTest* tc)
{
	// TODO
}

// FFT and 3rd party lib exploration tests

void Test3rdPartyDCReference(CuTest* tc)
{
    int n = 8; // Data length (must be a power of 2)
    int ip[2 + (int)(sqrt(n + 0.5) / 2)]; // Work area for bit reversal
    double w[n / 2]; // Cos/Sin table
    double data[2 * n]; // Input/output data

    // Initialize the input data (DC)
    data[0] = 2.0;
    data[1] = 0.0;
    data[2] = 2.0;
    data[3] = 0.0;
    data[4] = 2.0;
    data[5] = 0.0;
    data[6] = 2.0;
    data[7] = 0.0;
    data[8] = 2.0;
    data[9] = 0.0;
    data[10] = 2.0;
    data[11] = 0.0;
    data[12] = 2.0;
    data[13] = 0.0;
    data[14] = 2.0;
    data[15] = 0.0;

    // Perform Complex DFT
    ip[0] = 0; // Initialize the work area (first time only)
    cdft(2 * n, 1, data, ip, w);

    // Print the output data
    printf("DFT Results:\n");
    for (int i = 0; i < n; i++) {
		
		// Divide by nbr points
		data[2 * i] *= 1.0 / n;
		data[2 * i + 1] *= 1.0 / n;
		
		//double amplitude = 2 * sqrt(data[2 * i] * data[2 * i] + data[2 * i + 1] * data[2 * i + 1]); // TODO: Check amplitude
		
		// TODO: Assert
    }
}

void Test3rdPartyTwoSinesReference(CuTest* tc)
{
    int n = FRAME_SIZE; // Data length (must be a power of 2)
    int ip[2 + (int)(sqrt(n + 0.5) / 2)]; // Work area for bit reversal
    double w[n / 2]; // Cos/Sin table
    double data[2 * n]; // Input/output data

	// Initialize the input data (Sine 1 + Sine 2)
	double time_delta = 1.0 / SAMPLE_RATE;
    for (int i = 0; i < n; i++) {
		double time = time_delta * i;
		data[2 * i] = TEST_DC_OFFSET + TEST_AMPL1 * sin(2 * M_PI * TEST_FREQ1 * time) + TEST_AMPL2 * sin(2 * M_PI * TEST_FREQ2 * time);
		data[2 * i + 1] = 0;
    }

    // Perform Complex DFT
    ip[0] = 0; // Initialize the work area (first time only)
    cdft(2 * n, 1, data, ip, w);
	
	// Calculate top frequency
	double correction = n % 2 == 0 ? 1 : ((double)n - 1) / n; // Should always be even since power of 2 but kept here for reference
	double top_freq = (SAMPLE_RATE / 2.0) * correction;
	
	// Calculate number of frequencies in result
	int nbr_freqs = (n / 2) + 1; // floor(n/2) + 1(DC)

    // Print the output data
    for (int i = 0; i < nbr_freqs; i++) {
		
		// Divide by nbr points
		data[2 * i] *= 1.0 / n;
		data[2 * i + 1] *= 1.0 / n;
		
		double frequency = (double)i * (top_freq / (nbr_freqs - 1));
		
		CuAssertTrue(tc, frequency <= top_freq);
		
		int is_dc_or_nyquist = (i == 0 || i == (nbr_freqs - 1));
		double scaling_factor = is_dc_or_nyquist ? 1.0 : 2.0; // Excluding DC and Nyquist
		double amplitude = scaling_factor * sqrt(data[2 * i] * data[2 * i] + data[2 * i + 1] * data[2 * i + 1]); // 2x since amplitude split between positive and negative frequencies
		
		if (i == 0) {
			CuAssertTrue(tc, amplitude > 1.998);
			CuAssertTrue(tc, amplitude < 2.002);
		}
		
		// F = 109.863281 X[225] = 0.001884 + 0.000019j, A[225] = 0.003769
		if (fabs(frequency - 110) < 0.25 && frequency < TEST_FREQ1) {
			CuAssertTrue(tc, amplitude < 0.01); // Ideally == 0
		}

		// F = 220.214844 X[451] = -1.047368 + 0.200496j, A[451] = 2.132772
		if (fabs(frequency - TEST_FREQ1) < 0.25) {
			CuAssertTrue(tc, amplitude > 2); // Ideally == 3, scalloping loss
			CuAssertTrue(tc, amplitude <= 3.002); // Ideally == 3
		}

		// F = 439.941406 X[901] = 0.896440 + 2.270916j, A[901] = 4.882893
		if (fabs(frequency - TEST_FREQ2) < 0.25) {
			CuAssertTrue(tc, amplitude > 4); // Ideally == 5, scalloping loss
			CuAssertTrue(tc, amplitude <= 5.002); // Ideally == 5
		}
    }
}
