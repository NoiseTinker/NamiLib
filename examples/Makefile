# Directories
SRCDIR = ./
OUTDIR = ./out
IDIR = ../src/include

# Files

_EXECUTABLES = morse_dit play_sdr_file play_sdr_socket psk31_zeros
EXECUTABLES = $(patsubst %,$(OUTDIR)/%,$(_EXECUTABLES))

# Toolchain

CC = gcc
CFLAGS = -I$(IDIR) -Wall -Werror -pedantic -std=c99 -I../src/include -lportaudio ../out/libNami.a

# Make stuff

.PHONY: all
.PRECIOUS: %/.d

# To handle dependencies to output directories

%/.d:
	mkdir -p $(@D)
	touch $@

# Build

all: $(EXECUTABLES)

$(OUTDIR)/%: $(SRCDIR)/%.c $(OUTDIR)/.d
	$(CC) -o $@ $< $(CFLAGS)

# Clean

clean:
	rm -rf $(OUTDIR)
