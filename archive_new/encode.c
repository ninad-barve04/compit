#include <stdio.h>
#include <string.h>
#include <float.h>
#include "debug.h"
#include "encode.h"
#include "constants.h"


int bitsToWrite =0;
int buffer = 0;
int byteBuff = 0;

void encode_byte( int byte, FILE *op_fp, ProbabilityDistribution *pdistib){

    ProbabilityDistribution pd = (*pdistib);
    float current_range = pd.upper - pd.lower;
    pd.upper = pd.lower + ((current_range * pd.range[byte]) / pd.cumulative_prob);
    if( byte == 0){
        pd.lower = 0.0;
    }
    else{
        pd.lower = pd.lower + ((current_range * pd.range[byte - 1]) / pd.cumulative_prob);

    }
    for(;;){
        debug_print("Lower: %lf\tUpper: %lf\nByte: %hx, Byte Range: %d\n", pd.lower, pd.upper, byte, pd.range[byte]);
        if( pd.upper < HALF){
            write_bit(0, op_fp);
        }
        else if( pd.lower >= HALF){
            write_bit(1, op_fp);
            pd.upper = pd.upper - HALF;
            pd.lower = pd.lower - HALF;
            
        }
        else if( pd.lower >= FIRST_QUARTER  && pd.upper < THIRD_QUARTER){
            bitsToWrite++;
            pd.upper = pd.upper - FIRST_QUARTER ;
            pd.lower = pd.lower - FIRST_QUARTER;
        }
        else{
            //debug_print("breaking\n");
            break;
        }
        pd.lower = pd.lower * 2;
        pd.upper = pd.upper * 2;
    }
    // debug_print("Lower: %lf\tUpper: %lf\nByte: %hx, Byte Range: %d\n\n", pd.lower, pd.upper, byte, pd.range[byte]);

    *pdistib = pd;
}


void encode_file(FILE *ip_fp, FILE *op_fp) {
    unsigned char bit_list[BUFFER_SIZE];
    int encUnit;
    unsigned long total_count = 0;
    unsigned char compressing_buffer[ENCODING_BUFFER];
    long double encoded_number;

    /* 
     * Probability distribution is an array of length 256, which stores the 
     * count each byte occurs. This also is the lower bound for the probability 
     * distribution of all the bytes. 
     */
    ProbabilityDistribution pd;
    memset(pd.range, 0, sizeof(pd.range)); // Set array elements to 0


    memset(bit_list, 0, sizeof(bit_list));

    // for (int i = 0; i < sizeof(bit_list); i++) {
    //     debug_print("%hx\n", bit_list[i]);
    // }

    /*
     * Following while loop counts the number of times each byte appears in the  
     * bytestream.
     */
    while ((encUnit = fgetc(ip_fp)) != EOF) {
        bit_list[encUnit]++;
        total_count++;
    }
    pd.cumulative_prob = total_count;
    
    /*
     * Now populate probability distribution array
     */
    int total = 0;


    for (int i = 0; i < sizeof(bit_list); i++) {
        pd.range[i] = pd.range[i-1] + bit_list[i];
        total = total + bit_list[i];
        // debug_print("size = %d\n", bit_list[i]);
    }

    for (int i = 0; i < sizeof(bit_list); i++) {
        debug_print("%hx\t%hx\t%hx\n", i, bit_list[i], pd.range[i]);
    }
    debug_print("Total = %d\n", total);

    /*
     * The array forms a lookup header at the top of the file
     */
    // for (int i = 0; i < sizeof(bit_list); i++) {
    //     fwrite(&i, sizeof(unsigned char), 1, op_fp);
    //     fwrite(&(pd.range[i]), sizeof(unsigned short), 1, op_fp);
    // }

    debug_print("Total Byte Count = %lu\n", total_count);

    /*
     * The previous pass of the file was to create the lookup table as a header 
     * in the compression output file. Going back to the start of the file, 
     * actual encoding pass of the file takes place
     */
    rewind(ip_fp);
    pd.lower = 0.0;
    pd.upper = 1.0;

    float current_range = 0;

    // read each encoding unit ( char) from file and encode it
    // encoding works on entire file in one go and generates
    // series of encoded bytes which are written to file in buffered mode
    // 

    while ((encUnit = fgetc(ip_fp)) != EOF) {
        // pd.upper = pd.range[(char) byte];
        // pd.lower = pd.range[(char) (byte - 1)];
        // debug_print("while Upper: %hx  Lower: %hx\n", pd.upper, pd.lower);
        // unsigned short value_range =pd.upper - pd.lower;

        encode_byte( encUnit, op_fp, &pd);
         
    }
    // encode end of file (EOF) char
    // encode_byte(0,op_fp,&pd);
    
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
   
}
void write_bit(int number, FILE *fp){

    buffer_and_write_out(number, fp);
    while (bitsToWrite > 0)
	{
		buffer_and_write_out(!number,fp);
		bitsToWrite--;
	}
 
 
}

void encode_bitstream(unsigned char buffer[ENCODING_BUFFER], ProbabilityDistribution *pd_lookup) {

}
