.PHONY: all

all:
	racket linker-scripts.rkt
	racket io.rkt
	racket system.rkt
	racket hw.rkt
