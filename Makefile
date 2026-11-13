CC ?= cc
CPPFLAGS ?= -Iinclude
CFLAGS ?= -std=c11 -Wall -Wextra -O2
LDFLAGS ?=
LDLIBS ?= -lm

.PHONY: all clean

all: build/softmax

build/softmax: build/softmax.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

build/softmax.o: src/softmax.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c -o $@ $<

build:
	mkdir -p $@

-include build/softmax.d

clean:
	rm -f build/softmax build/softmax.o build/softmax.d
