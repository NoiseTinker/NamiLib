NamiLib
=======

A library for basic signal generation and processing implemented in C.

Written as exercise.

Features
--------

* Sine, square, triangle and sawtooth _Periodic_ functions.
* ADSR and raised-cosine _Envelope_ function.
* Parameterized _Wave_ from periodic function and envelope.
* _Sampler_ to take samples from a _Wave_.
* PCM _Frame_ to handle the samples.
* _Fft_ using Ooura's FFT implementations.
* _FrameWriter_ to write frames to a file.

Backlog
-------

* Waypoint periodic function.
* File input.

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

Examples
--------

### Sine wave with raised cosine envelope (clickless Morse dit)


### PSK31 Zero


### FFT pass band filter

Reference
---------
<https://en.wikipedia.org/wiki/Wave>
<https://en.wikipedia.org/wiki/Waveform>
<http://www.kurims.kyoto-u.ac.jp/~ooura/fft.html>
