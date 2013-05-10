all: main
	gcc main.o runlength_compress.o runlength_decompress.o -o t2emanuel

main: runlength_compress main.c
	gcc -c main.c -o main.o

runlength_compress: runlength_decompress runlength_compress.h runlength_compress.c
	gcc -c runlength_compress.c -o runlength_compress.o

runlength_decompress: runlength_decompress.h runlength_decompress.c
	gcc -c runlength_decompress.c -o runlength_decompress.o

clean:
	rm *.o

run:
	./t2emanuel

zip:
	zip -r t2emanuel.zip *.c *.h Makefile
