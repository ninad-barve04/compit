/**
 * @file main.c
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "index_table.h"
#include "encode.h"
#include "decode.h"


int main(int argc, char *const argv[])
{
    char ip_filename[1024];
    char op_filename[1024];
    
	if (argc < 4) {
        printf("Usage: ./CompIt <encode/decode> <input_filename> <output_filename>\n");
        return -1;
    }

    if (argv[1][0] == 'e' || argv[1][0] == 'E') {
        printf("Encoding %s\n", argv[2]);
        FILE *input_file = fopen(argv[2], "rb");
        FILE *encoded_op = fopen(argv[3], "wb");
        if (input_file == NULL || encoded_op == NULL) {
            printf("Invalid filename! %s %s\n", argv[2], argv[3]);
            return -1;
        }

        encode_file(input_file, encoded_op);
        fclose(encoded_op);
        fclose(input_file);
        printf("File encoded+compressed successfully\n");
    }
    else if (argv[1][0] == 'd' || argv[1][0] == 'D') {
        printf("Decoding %s\n", argv[2]);
        
        FILE *input_file = fopen(argv[2], "rb");
        FILE *decoded_op = fopen(argv[3], "wb");
        if (input_file == NULL || decoded_op == NULL) {
            printf("Invalid filename!\n");
            return -1;
        }

        decode_file(input_file, decoded_op);
        fclose(decoded_op);
        fclose(input_file);
        printf("File decoded successfully\n");

    } else {
        printf("Invalid operation input!\n");
        printf("Usage: ./CompIt <encode/decode> <input_filename> <output_filename>\n");
        return -1;
    }

    return 0;
}

