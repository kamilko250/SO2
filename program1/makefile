$(OBJ): lib.h
all: main.o lib.o 
	gcc -o Program1.out main.o lib.o -pthread
	make clean 

main.o: main.c
	gcc -c -o main.o main.c

demonlib.o: lib.c
	gcc -c -o lib.o lib.c

clean: 
	rm -rvf *.o 