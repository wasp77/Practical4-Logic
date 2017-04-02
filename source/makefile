ttable : ttable.o
	clang ttable.o -o ttable

ttable2 : ttable2.o
	clang ttable2.o -o ttable2

ttable.o : ttable.c logic.h
	clang -Wall -Wextra ttable.c -c

ttable2.o : ttable2.c logic.h
	clang -Wall -Wextra ttable2.c -c

clean :
	rm -f ttable.o ttable2.o ttable ttable2
