CompIt: main.o encode.o decode.o debug.o index_table.o constants.o
	gcc main.o encode.o decode.o debug.o index_table.o constants.o -o CompIt

debugIt:
	gcc -g main.c encode.c decode.c debug.c constants.c index_table.c -DDEBUGPR -o CompDbgIt

clean:
	-rm *.o
	-rm CompIt
	-rm debugIt
