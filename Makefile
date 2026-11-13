CC ?= cc
CPPFLAGS ?= -Iinclude
CFLAGS ?= -std=c11 -Wall -Wextra -O2
LDFLAGS ?=
LDLIBS ?= -lm
UNITY_DIR := build/unity-2.6.1
UNITY_URL := https://raw.githubusercontent.com/ThrowTheSwitch/Unity/v2.6.1/src
UNITY_FILES := $(addprefix $(UNITY_DIR)/,unity.c unity.h unity_internals.h)

.PHONY: all clean test

all: build/softmax

test: build/softmax_test
	./build/softmax_test

build/softmax_test: tests/softmax_test.c src/softmax.c $(UNITY_FILES) | build
	$(CC) $(CPPFLAGS) -I$(UNITY_DIR) -DUNITY_INCLUDE_DOUBLE $(CFLAGS) $(LDFLAGS) -o $@ $(filter %.c,$^) $(LDLIBS)

$(UNITY_DIR)/unity.c: UNITY_SHA256 := b90e735a54cf3b3765ab6caa955d11a1488ee73d9c6152cdc98576c2d17cb871
$(UNITY_DIR)/unity.h: UNITY_SHA256 := 9db174d3c2c6424fd35c0980c5941d124c5ebb0f48e8172f997a2aa9554b64ea
$(UNITY_DIR)/unity_internals.h: UNITY_SHA256 := fcd8b3f6b412ac0ab599547eb8a30b6d7f3f0af77aab31f7a1822a2a8fc9a2b2

$(UNITY_FILES): | $(UNITY_DIR)
	@set -e; trap 'rm -f "$@.tmp"' EXIT; \
		curl -fsSL "$(UNITY_URL)/$(@F)" -o "$@.tmp"; \
		printf '%s  %s\n' '$(UNITY_SHA256)' "$@.tmp" | sha256sum -c -; \
		mv "$@.tmp" "$@"

$(UNITY_DIR): | build
	mkdir -p $@

build/softmax: build/softmax.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

build/softmax.o: src/softmax.c | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c -o $@ $<

build:
	mkdir -p $@

-include build/softmax.d

clean:
	rm -f build/softmax build/softmax.o build/softmax.d build/softmax_test
	rm -f $(UNITY_FILES)
