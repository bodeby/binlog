# fast commands

.PHONY: build encode decode test bench

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
