all: main
	gcc main.o runlength.o -o t2emanuel
main: main.c runlength
	gcc -c main.c -o main.o
runlength:  runlength.h runlength.c
	gcc -c runlength.c -o runlength.o
clean:
	rm *.o
run:
	./t2emanuel
zip:
	zip -r t2emanuel.zip *.c *.h Makefile
