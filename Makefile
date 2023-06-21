# Directories
FFTSRCDIR = ./ext/fft
SRCDIR = ./src
TESTDIR = ./test
OUTDIR = ./out
ODIR = $(OUTDIR)/obj
TESTODIR = $(OUTDIR)/test-obj
TESTOUTDIR = $(OUTDIR)/test-output
IDIR = ./src/include

# Toolchain

CC = clang
CFLAGS = -I$(IDIR) -Wall -Werror -pedantic -std=c99
AR = ar

# Files

FFTIMPL = fftsg

LIB = libNami.a

_DEPS = Gain.h ComplexNumber.h Fft.h Periodic.h Envelope.h Wave.h Frame.h FrameWriter.h \
 FrameReader.h FramePlayer.h FrameRecorder.h Sampler.h Oscillator.h Demodulator.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Gain.o ComplexNumber.o Fft.o Periodic.o Envelope.o Wave.o Frame.o FrameWriter.o \
 FrameReader.o FramePlayer.o FrameRecorder.o Sampler.o Oscillator.o Demodulator.o fftsg.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
TESTOBJ = $(patsubst %,$(TESTODIR)/%,$(_OBJ))

_TESTS = GainTest.o FftTest.o PeriodicTest.o EnvelopeTest.o WaveTest.o SamplerTest.o \
 FrameWriterTest.o FrameReaderTest.o OscillatorTest.o DemodulatorTest.o CuTest.o AllTests.o
TESTS = $(patsubst %,$(TESTODIR)/%,$(_TESTS))

# Make stuff

.PHONY: main test gentests profile clean
.PRECIOUS: %/.d

# To handle dependencies to output directories

%/.d:
	mkdir -p $(@D)
	touch $@

# Build

main: $(OUTDIR)/$(LIB)

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(ODIR)/.d
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(ODIR)/fftsg.o: $(FFTSRCDIR)/$(FFTIMPL).c $(ODIR)/.d
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(LIB): $(OBJ) $(OUTDIR)/.d
	$(AR) rs $@ $^
	$(AR) d $@ .d

# Test

test: $(OUTDIR)/test-$(LIB) $(TESTS) $(OUTDIR)/gcov/.d $(TESTOUTDIR)/.d
	clang $(TESTS) -o $(OUTDIR)/run-all-tests -I./test $(CFLAGS) $(OUTDIR)/test-$(LIB) -fprofile-arcs -ftest-coverage
	$(OUTDIR)/run-all-tests
	gcov -l -o$(TESTODIR) $(SRCDIR)/*.c 2> /dev/null > $(OUTDIR)/gcov/summary.txt
	mv *.gcov $(OUTDIR)/gcov

$(TESTDIR)/AllTests.c: $(TESTDIR)/*.c
	$(TESTDIR)/make-tests.sh $(TESTDIR)/*.c > $(TESTDIR)/AllTests.c

$(TESTODIR)/%.o: $(TESTDIR)/%.c $(DEPS) $(TESTODIR)/.d $(TESTDIR)/AllTests.c
	$(CC) -g -c -o $@ $< $(CFLAGS)

$(TESTODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(TESTODIR)/.d
	$(CC) -g -c -o $@ $< $(CFLAGS) -fprofile-arcs -ftest-coverage

$(TESTODIR)/fftsg.o: $(FFTSRCDIR)/$(FFTIMPL).c $(TESTODIR)/.d
	$(CC) -g -c -o $@ $< $(CFLAGS) -fprofile-arcs -ftest-coverage

$(OUTDIR)/test-$(LIB): $(TESTOBJ) $(OUTDIR)/.d
	$(AR) rs $@ $^
	$(AR) d $@ .d

# Profile

profile: $(OUTDIR)/profile.log

$(OUTDIR)/profile.log: $(OUTDIR)/callgrind
	callgrind_annotate $< > $@
	cat $@

$(OUTDIR)/callgrind: $(OUTDIR)/test-$(LIB) gentests $(TESTS)
	$(CC) $(TESTS) -o $(OUTDIR)/run-all-tests -I./test $(CFLAGS) $(OUTDIR)/test-$(LIB) -fprofile-arcs -ftest-coverage
	valgrind --dsymutil=yes --tool=callgrind --callgrind-out-file=$@ $(OUTDIR)/run-all-tests

# Clean

clean:
	rm -rf $(OUTDIR)
	rm $(TESTDIR)/AllTests.c
