NamiLib
=======

A small and simple library for basic signal generation and processing implemented in C.

Written to learn about DSP.

Features
--------

* Sine, square, triangle and sawtooth _Periodic_ functions.
* ADSR and raised-cosine _Envelope_ function.
* Parameterized _Wave_ from periodic function and envelope.
* _Sampler_ to take samples from a _Wave_.
* PCM _Frame_ to handle the samples.
* _Oscillator_ producing real or complex (IQ) signal.
* _Fft_ using Ooura's FFT implementations.
* _FrameWriter_ to write frames to a file.
* _FrameReader_ to read frames from a file.

Backlog
-------

* Rectangular, Hamming or Hanning _Window_.
* _ComplexFrame_ for IQ signals.
* _Stft_ to create waterfall displays etc.
* _Demodulator_ and _Modulator_ for LSB, USB, CW and AM.
* _FrameRecorder_ to record frames from sound card.
* _FramePlayer_ to play frames to sound card.
* Goertzel algorithm for DTMF detection.
* Waypoint periodic function.

Build
-----

    make

To cross-compile for e.g. AVR:

    make CROSS_COMPILE=avr- MACH=atmega328

Test
----

    make test

Building blocks
---------------

The library provide a few building blocks that can be used to create wave forms.

### Wave form synthesis

    | Periodic function | ( -1 <= y <= 1, 0 <= x <= 2π )
              |
              \---------------> * <--------- | Envelope |
                                |
                                V
                            | Wave | <-  f, phase, A
                                |
                                V
                           | Sampler | <- sampling frequency, t1, t2 
                                |
                                V
                            | Frame | <- encoding
                                |
                                V
                         | FrameWriter |

### Signal processing

    | FrameReader |
          |
          V
      | Frame |
          |
          V
         FFT()
          |
          V
    ComplexNumber[]     ComplexNumber[]
          |                   |
          \---------*---------/
                    |
                    V
                  IFFT()
                    |
                    V
                | Frame |

    | FrameRecorder |          | Oscillator |
           |                        |
           V                        V
    | ComplexFrame |         | ComplexFrame |
           |                        |
           \--> | Demodulator | <---/
                       |
                       V
                   | Frame | -> | Stft | -> | ComplexFrame |
                       |
                | FramePlayer |

Examples
--------

### Sine wave with raised cosine envelope (clickless Morse dit)

#### Code

    uint8_t data[FRAME_SIZE] = {0};

    double angularFrequency = angularFrequencyFromFrequency(440);
    params.riseTime = 0.020;
    params.fallTime = 0.020;
    params.sustainTime = 0.040;

    setFunction(&periodic, &sine_wave);
    setEnvelopeFunction(&envelope, raisedCosine, (void*)&params);
    setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
    setEnvelope(&wave, &envelope);
    initSampler(&sampler, &wave, 0, 0.080, SAMPLE_RATE);
    initFrame(&frame, UINT8, &data, FRAME_SIZE);
    openFrameWriter(&frameWriter, "out/test-output/enveloped_sine_test.raw");

    while (samplesLeft(&sampler) > 0) {

        fillFrame(&sampler, &frame);
        writeFrame(&frameWriter, &frame);
    }

    closeFrameWriter(&frameWriter);

#### Waveform

Waveform as viewed in Audacity:

![MorseDit](https://github.com/daijo/NamiLib/raw/master/examples/morse_dit.png)

[Morse Dit (Ogg Vorbis)](https://github.com/daijo/NamiLib/raw/master/examples/morse_dit.ogg)

### PSK31 Zeros

#### Code

    uint8_t data[FRAME_SIZE] = {0};
    double angularFrequency = angularFrequencyFromFrequency(700);

    params.riseTime = 0.016;
    params.fallTime = 0.016;
    params.sustainTime = 0;

    setFunction(&periodic, &sine_wave);
    setEnvelopeFunction(&envelope, raisedCosine, (void*)&params);
    setPeriodic(&wave, &periodic, 0.5, 0, angularFrequency);
    setEnvelope(&wave, &envelope);
    initSampler(&sampler, &wave, 0, 0.032, SAMPLE_RATE);
    initFrame(&frame, UINT8, &data, FRAME_SIZE);
    openFrameWriter(&frameWriter, "out/test-output/psk31_zeros_test.raw");

    for (int i = 0; i < 40; i++) {

        while (samplesLeft(&sampler) > 0) {

            fillFrame(&sampler, &frame);
            writeFrame(&frameWriter, &frame);
        }

        wave.phase += M_PI;
        setCurrentSampleTime(&sampler, 0);
    }

    closeFrameWriter(&frameWriter);

#### Waveform

Waveform as viewed in Audacity:

![Psk31Zeros](https://github.com/daijo/NamiLib/raw/master/examples/psk31_zeros.png)

[PSK31 Zeros (Ogg Vorbis)](https://github.com/daijo/NamiLib/raw/master/examples/psk31_zeros.ogg)

### FFT pass band filter

Reference
---------
<https://en.wikipedia.org/wiki/Wave>
<https://en.wikipedia.org/wiki/Waveform>
<http://www.kurims.kyoto-u.ac.jp/~ooura/fft.html>
