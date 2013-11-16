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

CC = gcc
CFLAGS = -I$(IDIR) -Wall -Werror -pedantic -std=c99
AR = ar

# Files

FFTIMPL = fftsg

LIB = libNami.a

_DEPS = ComplexNumber.h Fft.h Periodic.h Envelope.h Wave.h Frame.h FrameWriter.h \
 FrameReader.h Sampler.h Oscillator.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ComplexNumber.o Fft.o Periodic.o Envelope.o Wave.o Frame.o FrameWriter.o \
 FrameReader.o Sampler.o Oscillator.o fftsg.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
TESTOBJ = $(patsubst %,$(TESTODIR)/%,$(_OBJ))

_TESTS = FftTest.o PeriodicTest.o EnvelopeTest.o WaveTest.o SamplerTest.o \
 FrameWriterTest.o FrameReaderTest.o OscillatorTest.o CuTest.o AllTests.o
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
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/fftsg.o: $(FFTSRCDIR)/$(FFTIMPL).c $(ODIR)/.d
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(LIB): $(OBJ) $(OUTDIR)/.d
	$(AR) rs $@ $^

# Test

test: $(OUTDIR)/test-$(LIB) $(TESTS) $(OUTDIR)/gcov/.d $(TESTOUTDIR)/.d
	clang $(TESTS) -o $(OUTDIR)/run-all-tests -I./test $(CFLAGS) $(OUTDIR)/test-$(LIB) -fprofile-arcs -ftest-coverage
	$(OUTDIR)/run-all-tests
	gcov -l -o$(TESTODIR) $(SRCDIR)/*.c 2> /dev/null > $(OUTDIR)/gcov/summary.txt
	mv *.gcov $(OUTDIR)/gcov

$(TESTDIR)/AllTests.c: $(TESTDIR)/*.c
	$(TESTDIR)/make-tests.sh $(TESTDIR)/*.c > $(TESTDIR)/AllTests.c

$(TESTODIR)/%.o: $(TESTDIR)/%.c $(DEPS) $(TESTODIR)/.d $(TESTDIR)/AllTests.c
	clang -c -o $@ $< $(CFLAGS)

$(TESTODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(TESTODIR)/.d
	clang -c -o $@ $< $(CFLAGS) -fprofile-arcs -ftest-coverage

$(TESTODIR)/fftsg.o: $(FFTSRCDIR)/$(FFTIMPL).c $(TESTODIR)/.d
	clang -c -o $@ $< $(CFLAGS) -fprofile-arcs -ftest-coverage

$(OUTDIR)/test-$(LIB): $(TESTOBJ) $(OUTDIR)/.d
	$(AR) rs $@ $^

# Profile

profile: $(OUTDIR)/profile.log

$(OUTDIR)/profile.log: $(OUTDIR)/callgrind
	callgrind_annotate $< > $@
	cat $@

$(OUTDIR)/callgrind: $(OUTDIR)/test-$(LIB) gentests $(TESTS)
	clang $(TESTS) -o $(OUTDIR)/run-all-tests -I./test $(CFLAGS) $(OUTDIR)/test-$(LIB) -fprofile-arcs -ftest-coverage
	valgrind --dsymutil=yes --tool=callgrind --callgrind-out-file=$@ $(OUTDIR)/run-all-tests

# Clean

clean:
	rm -rf $(OUTDIR)
	rm $(TESTDIR)/AllTests.c
