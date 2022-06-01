CompIt: main.o encode.o decode.o
	gcc main.o encode.o decode.o -o CompIt

debugIt: 
	gcc -g main.c encode.c decode.c

clean:
	-rm *.o
	-rm CompIt

