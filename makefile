fibNum=1000000
fib.out:
ifeq (,$(wildcard /usr/local/include/gmpxx.h))
	make gmpGet
endif
	g++ fibonacci.cpp -o fib.out -lgmpxx -lgmp

gmpGet:
ifeq (,$(wildcard gmp-6.1.2.tar.xz))
	wget https://gmplib.org/download/gmp/gmp-6.1.2.tar.xz 
endif
	tar -xf gmp-6.1.2.tar.xz
	cd gmp-6.1.2 && ./configure --enable-cxx && sudo make && sudo make install && sudo make check
	sudo rm -r gmp*

test: fib.out
	./fib.out>fibQuick $(fibNum) 2
	./fib.out>fibSlow $(fibNum) 2 1
	cmp --silent fibQuick fibSlow && echo "SUCCESS" || "FAILURE"
	rm fibQuick fibSlow

fibQuick: fib.out
	./fib.out $(fibNum)

fibSlow: fib.out
	./fib.out $(fibNum) 0 1

clean:
	rm *.out

$(VERBOSE).SILENT: 
