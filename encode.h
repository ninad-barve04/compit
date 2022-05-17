#ifndef BIN_FILE_READ_H
#define BIN_FILE_READ_H (1)

#include "constants.h"

typedef struct ProbabilityDistribution {
    unsigned short range[BUFFER_SIZE + 2];

} ProbabilityDistribution;

void encode_file(FILE *ip_fp, FILE *op_fp);
void encode_bitstream(unsigned char buffer[ENCODING_BUFFER], ProbabilityDistribution pd_lookup);

#endif // BIN_FILE_READ_H


