CompIt: main.o encode.o decode.o debug.o
	gcc main.o encode.o decode.o debug.o -o CompIt

debugIt: 
	gcc -g main.c encode.c decode.c debug.c -DDEBUGPR -o CompDbgIt

clean:
	-rm *.o
	-rm CompIt

