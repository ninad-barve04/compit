#include <stdio.h>
#include <string.h>

#include "encode.h"
#include "constants.h"

void encode_file(FILE *ip_fp, FILE *op_fp) {
    unsigned char bit_list[BUFFER_SIZE];
    unsigned int byte;
    unsigned long totalCount = 0;
    unsigned char compressing_buffer[ENCODING_BUFFER];

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
        totalCount++;
    }

    
    /*
     * Now populate probability distribution array
     */
    for (int i = 0; i < sizeof(bit_list); i++) {
        pd.range[i+1] = pd.range[i] + bit_list[i];
    }

    for (int i = 0; i < sizeof(bit_list); i++) {
        printf("%hx\t%d\t%hx\n", i, bit_list[i], pd.range[i]);
    }

    /*
     * The array forms a lookup header at the top of the file
     */
    for (int i = 0; i < sizeof(bit_list); i++) {
        fwrite(&i, sizeof(unsigned char), 1, op_fp);
        fwrite(&(pd.range[i]), sizeof(unsigned short), 1, op_fp);
    }

    printf("Total Byte Count = %lu\n", totalCount);

    /*
     * The previous pass of the file was to create the lookup table as a header 
     * in the compression output file. Going back to the start of the file, 
     * actual encoding pass of the file takes place
     */
    rewind(ip_fp);

    while ((byte = fgetc(ip_fp)) != EOF) {
        
    }

}

void encode_bitstream(unsigned char buffer[ENCODING_BUFFER], ProbabilityDistribution pd_lookup) {

}