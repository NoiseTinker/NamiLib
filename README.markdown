NamiLib
=======

A small and simple library for basic signal generation, processing and software defined radio implemented in C.

Written to learn about DSP and SDR.

Features
--------

* Sine, square, triangle and sawtooth _Periodic_ functions.
* ADSR and raised-cosine _Envelope_ function.
* Parameterized _Wave_ from periodic function and envelope.
* _Sampler_ to take samples from a _Wave_.
* PCM _Frame_ to handle the samples.
* _Gain_ applies gain to a frame. 
* _Oscillator_ producing real or complex (IQ) signal.
* _Fft_ using Ooura's FFT implementations.
* _FrameWriter_ to write frames to a file.
* _FrameReader_ to read frames from a file.
* _FramePlayer_ to play frames to sound card.

Backlog
-------

* _Gain_ Also measures average level and DC offset.
* _AGC_ automatic gain control.
* _FrameRecorder_ to record frames from sound card or rtl-sdr.
* _ComplexFrame_ for IQ signals.
* _Demodulator_ and _Modulator_ for SSB, CW, AM and FM.
* _Stft_ to create waterfall displays etc.
* Rectangular, Hamming or Hanning _Window_.
* Goertzel algorithm for DTMF detection.
* Waypoint periodic function.

Dependencies
------------

Depends on portaudio and rtl-sdr.

    sudo port install portaudio rtl-sdr

Build
-----

    make

Test
----

    make test

Build Example
-------------

    gcc -I../src/include -lportaudio ../out/libNami.a play_sdr.c -o play_sdr

Building blocks
---------------

The library provide a few building blocks.

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

### Software Define Radio

    | FrameRecorder |
           |
           V
       | Frame |
           |
           V
        | AGC |
           |
           V
     | DcRemover | 
           |
           V
    | Deinterlacer |          | Oscillator |
           |                        |
           V                        V
    | ComplexFrame |         | ComplexFrame |
           |                        |
           \--> | Demodulator | <---/
                       |
                       V
                   | Frame | -> | Stft | -> | ComplexFrame |
                       |
                       V
                | FramePlayer |

### Streams

    | FrameRecorder |              | FrameReader |
            |                            |
            V                            V
        | Frame |                    | Frame |
            |                            |
            \--------------*-------------/
                           |
                          ...
                           |
                           V
            /--------------*-------------\
            |                            |
    | FramePlayer |                | FrameWriter |

Examples
--------

### Sine wave with raised cosine envelope (clickless Morse dit)

#### Code

    Periodic periodic;
    Envelope envelope;
    RaisedCosineParameters params;
    Wave wave;
    Sampler sampler;
    Frame frame;
    FrameWriter writer;
    uint8_t data[FRAME_SIZE] = {0};
    double angularFrequency = nami_angular_frequency_from_frequency(700);
    
    params.rise_time = 0.020;
    params.fall_time = 0.020;
    params.sustain_time = 0.040;
    
    nami_set_function(&periodic, &nami_sine_wave);
    nami_set_envelope_function(&envelope, nami_raised_cosine, (void*)&params);
    nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
    nami_set_envelope(&wave, &envelope);
    nami_init_sampler(&sampler, &wave, 0, 0.080, SAMPLE_RATE);
    nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
    nami_open_writer(&writer, "morse_dit.raw");
    
    while (nami_samples_left(&sampler) > 0) {
    
        nami_fill_frame(&sampler, &frame);
        nami_write_frame(&writer, &frame);
    }
    
    nami_close_writer(&writer);

#### Waveform

Waveform as viewed in Audacity:

![MorseDit](https://github.com/daijo/NamiLib/raw/master/examples/morse_dit.png)

[Morse Dit (Ogg Vorbis)](https://github.com/daijo/NamiLib/raw/master/examples/morse_dit.ogg)

### PSK31 Zeros

#### Code

    Periodic periodic;
    Envelope envelope;
    RaisedCosineParameters params;
    Wave wave;
    Sampler sampler;
    Frame frame;
    FrameWriter writer;
    uint8_t data[FRAME_SIZE] = {0};
    double angularFrequency = nami_angular_frequency_from_frequency(700);
    
    params.rise_time = 0.016;
    params.fall_time = 0.016;
    params.sustain_time = 0;
    
    nami_set_function(&periodic, &nami_sine_wave);
    nami_set_envelope_function(&envelope, nami_raised_cosine, (void*)&params);
    nami_set_periodic(&wave, &periodic, 0.5, 0, angularFrequency);
    nami_set_envelope(&wave, &envelope);
    nami_init_sampler(&sampler, &wave, 0, 0.032, SAMPLE_RATE);
    nami_init_frame(&frame, UINT8, &data, FRAME_SIZE);
    nami_open_writer(&writer, "psk31_zeros.raw");
    
    for (int i = 0; i < 40; i++) {
    
        while (nami_samples_left(&sampler) > 0) {
    
            nami_fill_frame(&sampler, &frame);
            nami_write_frame(&writer, &frame);
        }
    
        wave.phase += M_PI;
    
        nami_set_current_sample_time(&sampler, 0);
    }
    
    nami_close_writer(&writer);

#### Waveform

Waveform as viewed in Audacity:

![Psk31Zeros](https://github.com/daijo/NamiLib/raw/master/examples/psk31_zeros.png)

[PSK31 Zeros (Ogg Vorbis)](https://github.com/daijo/NamiLib/raw/master/examples/psk31_zeros.ogg)

### FFT pass band filter

Reference
---------
* <https://en.wikipedia.org/wiki/Wave>
* <https://en.wikipedia.org/wiki/Waveform>
* <http://www.kurims.kyoto-u.ac.jp/~ooura/fft.html>
* <http://www.portaudio.com/docs.html>
* <http://sdr.osmocom.org/trac/wiki/rtl-sdr>
* <http://www.dspguru.com/sites/dspguru/files/QuadSignals.pdf>
* <http://www.digitalsignallabs.com/Digradio.pdf>
