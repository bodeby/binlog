# fast commands

.PHONY: build encode decode test

# ------------------------
# Run / Debug (generic)
# ------------------------

all: build

build:
	cmake --preset debug
	cmake --build --preset debug

encode:
	cmake --preset debug
	cmake --build --preset debug
	./build/debug/apps/encode/binlog-encode

decode:
	cmake --preset debug
	cmake --build --preset debug
	./build/debug/apps/decode/binlog-decode

test:
	cmake --preset debug
	cmake --build --preset debug
	ctest --preset debug
