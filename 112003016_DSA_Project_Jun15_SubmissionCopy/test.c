#include <stdio.h>
#include <stdlib.h>
#include "encode.h"


int main(int argc, const char *argv[])
{

    FILE *infile = fopen(argv[1], "rb");
    FILE *outfile = fopen(argv[2], "wb");

  //  encodeFile( infile, outfile);

    int c1 = 12;
    char cx = (char)c1;
    char c2 = 'b';
    char c3 = 'c';

unsigned short cb1 = 0;
unsigned short cb2 = ~0;

printf("%u, %u\n", cb1,cb2);

    fwrite( &cx, sizeof( char), 1, outfile);
    fwrite( &c2, sizeof( char), 1, outfile);
    fwrite( &c3, sizeof( char), 1, outfile);

    fclose( infile);
    fclose( outfile);



}


