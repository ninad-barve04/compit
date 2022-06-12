#ifndef BIN_FILE_READ_H
#define BIN_FILE_READ_H (1)

#include "constants.h"

typedef struct ProbabilityDistribution {
    unsigned short range[BUFFER_SIZE + 2];
    unsigned long cumulative_prob;

    unsigned int total_count;

    float upper;
    float lower;
    
} ProbabilityDistribution;

void encode_file(FILE *ip_fp, FILE *op_fp);
void encode_bitstream(unsigned char buffer[ENCODING_BUFFER], ProbabilityDistribution *pd_lookup);
void write_bit(int bit, FILE *fp);
#endif // BIN_FILE_READ_H


