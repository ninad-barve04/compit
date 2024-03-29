/**
 * @file decode.c
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
#include <math.h>

#include "encode.h"
#include "decode.h"
#include "constants.h"
#include "debug.h"


int bitsInBuffer = 0;
int decodeBuffer = 0;

int decodval = 0;
int EOF_REACHED = 0;


int get_bit(FILE* decodeFile)
{
    int t;

    if (bitsInBuffer == 0) {
        char cc = 0;
        int x = fread(&cc, sizeof(char), 1, decodeFile);
        if (x == 0) {
            EOF_REACHED = 1;
            return -1;
        }
        decodeBuffer = cc;
        if (decodeBuffer < 0) {
            decodeBuffer = decodeBuffer + 256;
        }
        debug_print("%d\n", decodeBuffer);
        bitsInBuffer = 8;
    }
    t = decodeBuffer & 1;
    decodeBuffer >>= 1;
    bitsInBuffer--;
    return t;
}


int decode_first_byte(FILE* decoded_file)
{
    int value = 0;;
    for (int i = 1; i <= 16; i++) {
        int bt = get_bit(decoded_file);
        value = 2*value + bt;
    }

    return value;
}


int decode_byte( FILE* decoded_file, ProbabilityDistribution* pdistib)
{
    ProbabilityDistribution pd = (*pdistib);
    int current_range = pd.upper - pd.lower;
    
    int n = ((((decodval - pd.lower )+ 1) * pd.range[0]-1) / current_range);
    int i = 0;
    int low = pd.lower;
    int high = pd.upper;

    /* 
     * Calculate the upper and lower bounds to be subdivided for current 
     * decodeval 
     */
    for (i = 1; i < (BUFFER_SIZE + 2); i++) {
        if( pd.range[i]<=n){
            high = low + pd.range[i - 1] * current_range / pd.range[0];
            low = low + pd.range[i] * current_range / pd.range[0];
            break;
        }
    }

    /*
     * Change the ranges for maintaining the original precision exactly opposite 
     * to the encoding logic from the research paper 
     */
    for (;;) {
        if (high < HALF_RANGE)
        {
        }
        else if (low >= HALF_RANGE)
        {
            decodval -= HALF_RANGE;
            low -= HALF_RANGE;
            high -= HALF_RANGE;
        }
        else if (low >= FIRST_QUARTER_RANGE && high < THIRD_QUARTER_RANGE)
        {
            decodval -= FIRST_QUARTER_RANGE;
            low -= FIRST_QUARTER_RANGE;
            high -= FIRST_QUARTER_RANGE;
        }
        else
            break;
        low = 2 * low;
        high = 2 * high;
        decodval = 2* decodval + get_bit(decoded_file);
  
    }
    
    /*
     * Final upper and lower bounds for the decodeval character 
     */
    (*pdistib).lower = low;
    (*pdistib).upper = high;
   
    return i;
}


void decode_file(FILE *encoded, FILE *decoded_file) {
    
    ProbabilityDistribution pd;

    memset(pd.range, 0, sizeof(pd.range));
    pd.lower = 0;
    pd.upper = MAX_RANGE_VALUE;

    /*
     * Initialization of ProbabilityDistribution struct similar to encoding
     */
    initialize_indexes(&pd);

    /*
     * The first byte needs to be decoded separately into its coresponding 
     * integer. This decodedvalue(decodval) in required for decoding subsequent
     * bits.
     */
    int f1 = decode_first_byte(encoded);
        
    decodval = f1;

    /*
     * The decoding main loop is an inficite loop as the number of characters 
     * encoded is not specified in the file.
     * The infinite loop runs till a special encoded byte representing EOF is 
     * reached.
     * EOF_REACHED flag is raised and loop breaks.
     */
    while (1) {

        /*
         * Decode the single byte coming in as encoded
         */
        int decoded = decode_byte( encoded, &pd);

       
        if (EOF_REACHED == 1)
            break;
        int fchar;
        fchar = pd.indexChar[decoded];
        debug_print("%c\n", (char)fchar);
        fwrite(&fchar, sizeof(char), 1, decoded_file);
        update_indexes(decoded, &pd);
    }
    const char *endchar="00";
    fwrite(endchar, sizeof(char), 2, decoded_file);

   
    return;
}
