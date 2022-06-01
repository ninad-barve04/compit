#include <stdio.h>

#include "encode.h"
#include "constants.h"
#include "decode.h"


int main(int argc, char const *argv[])
{

    unsigned char buffer[] = "aaaaaaaa";

    //fwrite(buffer, sizeof(buffer), 1, fp);

    //fclose(fp);

    FILE *readFile = fopen(argv[1], "rb");
    FILE *output = fopen("output.ninad", "wb");

    encode_file(readFile, output);
    fclose(output);
    
    fclose(readFile);

    printf("Printing data from encoded output file:\n");
    output = fopen("output.ninad", "rb");

    FILE *decoded_output = fopen("output_decoded.ninad", "wb");
    decode_file(output, decoded_output);

    fclose(decoded_output);
    fclose(output);

    return 0;
}

