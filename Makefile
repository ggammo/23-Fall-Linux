exe : main.o copy.o
	gcc -o exe main.o copy.o
main.o : main.c copy.h
	gcc -c main.c
copy.o: copy.c copy.h
	gcc -c copy.c

clean : 
	rm -f *.o
