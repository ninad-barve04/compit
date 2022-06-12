/**
 * @file encode.c
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
#include <float.h>

#include "debug.h"
#include "constants.h"
#include "index_table.h"
#include "encode.h"



int bitsToWrite =0;
int buffer = 0;
int byteBuff = 0;


void end_encoding( FILE* op_fp, ProbabilityDistribution* pdistib)
{
    bitsToWrite++;
    if ((*pdistib).lower < FIRST_QUARTER_RANGE)
        write_bit(0, op_fp);
    else
        write_bit(1, op_fp);

    int out = buffer >> byteBuff;

    char cc = (char)out;
    fwrite(&cc, sizeof(char), 1, op_fp);

    return;
}


void encode_byte( int byte, FILE *op_fp, ProbabilityDistribution *pdistib){

    ProbabilityDistribution pd = (*pdistib);
    int test = 0;
   
    int current_range = pd.upper - pd.lower;
    pd.upper = pd.lower + ((current_range * pd.range[byte - 1]) / pd.range[0]);
  
    pd.lower = pd.lower + ((current_range * pd.range[byte]) / pd.range[0]);
 

    for(;;){
        debug_print("Lower: %lf\tUpper: %lf\nByte: %hx, Byte Range: %d\n", pd.lower, pd.upper, byte, pd.range[byte]);
        if( pd.upper < HALF_RANGE){
            write_bit(0, op_fp);
        }
        else if( pd.lower >= HALF_RANGE){
            write_bit(1, op_fp);
            pd.upper = pd.upper - HALF_RANGE;
            pd.lower = pd.lower - HALF_RANGE;
            
        }
        else if( pd.lower >= FIRST_QUARTER_RANGE  && pd.upper < THIRD_QUARTER_RANGE){
            bitsToWrite++;
            pd.upper = pd.upper - FIRST_QUARTER_RANGE;
            pd.lower = pd.lower - FIRST_QUARTER_RANGE;
        }
        else{
            //debug_print("breaking\n");
            break;
        }
        pd.lower = pd.lower * 2;
        pd.upper = pd.upper * 2;

        debug_print("%d\t%d\n", pd.lower, pd.upper);
    }
    // debug_print("Lower: %lf\tUpper: %lf\nByte: %hx, Byte Range: %d\n\n", pd.lower, pd.upper, byte, pd.range[byte]);
 
    *pdistib = pd;

    return;
}


void encode_file(FILE *ip_fp, FILE *op_fp) {
    int bit_list[BUFFER_SIZE];
    int encUnit;
    unsigned long total_count = 0;
    unsigned char compressing_buffer[ENCODING_BUFFER];
   


    /* 
     * Probability distribution is an array of length 256, which stores the 
     * count each byte occurs. This also is the lower bound for the probability 
     * distribution of all the bytes. 
     */
    ProbabilityDistribution pd;
    memset(pd.range, 0, sizeof(pd.range)); // Set array elements to 0
    memset(bit_list, 0, sizeof(bit_list));

    
    /*
     * Following while loop counts the number of times each byte appears in the  
     * bytestream.
     */
    int c = 0;
    int m = 0;
    while ((encUnit = fgetc(ip_fp)) != EOF) {
        bit_list[encUnit]++;
        total_count++;
    }
    pd.cumulative_prob = total_count;
    pd.total_count = total_count;
    
    // initialize probabilty and the cumulative frequency table
    initialize_indexes(&pd);

    
    debug_print("Total Byte Count = %lu\n", total_count);
    rewind(ip_fp);


    pd.lower = 0;
    pd.upper = MAX_RANGE_VALUE;

    float current_range = 0;

    /*
     * read each encoding unit ( char) from file and encode it
     * encoding works on entire file in one go and generates
     * series of encoded bytes which are written to file in buffered mode
     */

    while ((encUnit = fgetc(ip_fp)) != EOF) {
        int symbol = pd.encodedChars[encUnit];
        encode_byte( symbol, op_fp, &pd);
        update_indexes(symbol, &pd);
    }
    // encode end of file (EOF) char
    // encode_byte(0,op_fp,&pd);
    end_encoding(op_fp, &pd);
    
     return;
}


void buffer_and_write_out( int onebit, FILE *fp)
{
    debug_print("%d\t%d\t", onebit, buffer);
    buffer >>= 1;
    debug_print("%d\t", buffer);
	if (onebit){
		buffer |= 0x80;
	}
    debug_print("%d\n", buffer);
	byteBuff++;
	if (byteBuff == 8)
	{
        debug_print("out num %d\n", buffer);
        char cc = (char)buffer;
		fwrite(&cc, sizeof(char), 1, fp);
		byteBuff = 0;
	}
    return;
}


void write_bit(int number, FILE *fp){

    buffer_and_write_out(number, fp);
    while (bitsToWrite > 0)
	{
		buffer_and_write_out(!number,fp);
		bitsToWrite--;
	}
    return;
}

