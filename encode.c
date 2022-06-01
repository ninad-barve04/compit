#include <stdio.h>
#include <string.h>
#include <float.h>

#include "encode.h"
#include "constants.h"

void encode_file(FILE *ip_fp, FILE *op_fp) {
    unsigned char bit_list[BUFFER_SIZE];
    int byte;
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
    //     printf("%hx\n", bit_list[i]);
    // }

    /*
     * Following while loop counts the number of times each byte appears in the  
     * bytestream.
     */
    while ((byte = fgetc(ip_fp)) != EOF) {
        bit_list[byte]++;
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
        // printf("size = %d\n", bit_list[i]);
    }

    for (int i = 0; i < sizeof(bit_list); i++) {
        printf("%hx\t%hx\t%hx\n", i, bit_list[i], pd.range[i]);
    }
    printf("Total = %d\n", total);

    /*
     * The array forms a lookup header at the top of the file
     */
    for (int i = 0; i < sizeof(bit_list); i++) {
        fwrite(&i, sizeof(unsigned char), 1, op_fp);
        fwrite(&(pd.range[i]), sizeof(unsigned short), 1, op_fp);
    }

    printf("Total Byte Count = %lu\n", total_count);

    /*
     * The previous pass of the file was to create the lookup table as a header 
     * in the compression output file. Going back to the start of the file, 
     * actual encoding pass of the file takes place
     */
    rewind(ip_fp);
    pd.lower = 0.0;
    pd.upper = 1.0;

    float current_range = 0;

    while ((byte = fgetc(ip_fp)) != EOF) {
        // pd.upper = pd.range[(char) byte];
        // pd.lower = pd.range[(char) (byte - 1)];
        // printf("Upper: %hx  Lower: %hx\n", pd.upper, pd.lower);
        // unsigned short value_range =pd.upper - pd.lower;
        current_range = pd.upper - pd.lower;
        pd.upper = pd.lower + ((current_range * pd.range[byte]) / pd.cumulative_prob);
        pd.lower = pd.lower + ((current_range * pd.range[byte - 1]) / pd.cumulative_prob);

        printf("Lower: %lf\tUpper: %lf\nByte: %hx, Byte Range: %d\n", pd.lower, pd.upper, byte, pd.range[byte]);
    }
    
    encoded_number = (pd.upper + pd.lower) / (2.0);
    printf("Encoded Number: %.34Lg\nCount of characters: %ld\n", encoded_number, pd.cumulative_prob);

    fwrite(&encoded_number, sizeof(long double), 1, op_fp);
    fwrite(&(pd.cumulative_prob), sizeof(unsigned long), 1, op_fp);


    return;
}

void encode_bitstream(unsigned char buffer[ENCODING_BUFFER], ProbabilityDistribution *pd_lookup) {

}