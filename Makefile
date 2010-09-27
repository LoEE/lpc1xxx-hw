S := $(dir $(lastword $(MAKEFILE_LIST)))

io-pin.h: $Sio-pin.ss
	$Q racket $< > $(^:.ss=.h) || (rm $(^:.ss=.h) && exit 1)

clean:: $S
	-cd $<; rm -f io-pin.h *.d *.o
