.PHONY: all

all:
	racket linker-scripts.rkt
	rm -rf ../io
	mkdir -p ../io
	racket io.rkt
	racket io-lpc12xx.rkt
	racket io-lpc15xx.rkt
	racket io-lpc17xx.rkt
	rm -rf ../system
	mkdir -p ../system
	racket system.rkt
	racket system-lpc122x.rkt
	racket system-lpc15xx.rkt
	racket system-lpc17xx.rkt
	racket hw.rkt
