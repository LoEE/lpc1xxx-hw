.PHONY: all

all:
	racket linker-scripts.rkt
	rm -rf ../io
	mkdir -p ../io
	racket io.rkt
	racket io-lpc12xx.rkt
	rm -rf ../system
	mkdir -p ../system
	racket system.rkt
	racket system-lpc122x.rkt
	racket hw.rkt
