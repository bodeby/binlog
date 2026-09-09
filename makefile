# fast commands

.PHONY: build encode decode test bench bench-codspeed

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

# ------------------------
# Benchmarks
# ------------------------

BENCH ?= file_writer_benchmark

bench:
	cmake --preset release-bench
	cmake --build --preset release-bench
	./build/release-bench/bench/binlog/$(BENCH) \
		--benchmark_min_time=1s

# Runs the whole suite under CodSpeed's CPU simulation, exactly like CI.
# Requires the CodSpeed CLI: https://codspeed.io/docs/cli
bench-codspeed:
	cmake --preset codspeed
	cmake --build --preset codspeed --parallel
	codspeed run --mode simulation -- \
		sh -c 'set -e; for b in ./build/codspeed/bench/binlog/*_benchmark; do "$$b"; done'
