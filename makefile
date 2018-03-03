fibNum=1000000
fib.out:
	g++ fibonacci.cpp -o fib.out -lgmpxx -lgmp

test: fib.out
	./fib.out>fibQuick $(fibNum) 2
	./fib.out>fibSlow $(fibNum) 2 1
	diff -s fibQuick fibSlow
	rm fibQuick fibSlow

clear:
	rm *.out
