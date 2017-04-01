ttable : ttable.o
	clang ttable.o -o ttable

ttable.o : ttable.c logic.h
	clang -Wall -Wextra ttable.c -c

clean :
	rm -f ttable.o ttable
