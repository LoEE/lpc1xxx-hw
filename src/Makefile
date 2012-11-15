.PHONY: all

all:
	racket linker-scripts.rkt
	rm -rf ../io
	mkdir -p ../io
	racket io.rkt
	racket io-lpc12xx.rkt
	racket system.rkt
	racket hw.rkt
