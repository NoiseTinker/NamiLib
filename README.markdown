NamiLib
=======

A library for basic signal generation and processing implemented in C.

Written as exercise.

Features
--------

* _Fft_ using Ooura's FFT implementations.
* Sine, square, triangle and sawtooth _Periodic_ functions.
* ADSR and raised-cosine _Envelope_ function.
* Parameterized _Wave_ from periodic function and envelope.
* PCM _Frame_ to handle samples.

Backlog
-------

* Waypoint periodic function.
* File input/output (text, raw, GNUPlot).

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
              V
      | Wave equation | <-  f, phase, A -> | Wave equation |
              |                                   |
              \---------------> + <---------------/
                                |
                                |         | Wave equation |
                                V                 |
                                * <---------------/
                                |
                                V
                           | WaveForm | <- x,t1,t2 or t,x1,x2
                                |
                                V
                           | Sampler | <- sampling frequency, encoding
                                |
                                V
                            | Frame |

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

### Square wave from sine waves


### Gaussian enveloped sine wave (clickless Morse dit)


### PSK31 Zero


### FFT pass band filter

Reference
---------
<https://en.wikipedia.org/wiki/Wave>
<https://en.wikipedia.org/wiki/Waveform>
<http://www.kurims.kyoto-u.ac.jp/~ooura/fft.html>
