RED=\033[31m
GREEN=\033[5;32m
NORMAL=\033[0m
fibNum=1000000
fib.out: fibonacci.cpp
ifeq (,$(wildcard /usr/local/include/gmpxx.h))
	make gmpGet
endif
	g++ fibonacci.cpp -o fib.out -lgmpxx -lgmp

compare.out: fibCompare.cpp
ifeq (,$(wildcard /usr/local/include/gmpxx.h))
	make gmpGet
endif
	g++ fibCompare.cpp -o compare.out -lgmpxx -lgmp

compile: compare.out fib.out

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
	cmp --silent fibQuick fibSlow && echo "$(GREEN)SUCCESS$(NORMAL)" || "$(RED)FAILURE$(NORMAL)"
	$(RM) fibQuick fibSlow

fibQuick: fib.out
	./fib.out $(fibNum)

fibSlow: fib.out
	./fib.out $(fibNum) 0 1

compare: compare.out
	./compare.out

clean:
	$(RM) *.out *.swp *.swo

$(VERBOSE).SILENT: test
