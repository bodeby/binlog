# fast commands

.PHONY: build encode decode

# ------------------------
# Run / Debug (generic)
# ------------------------

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
