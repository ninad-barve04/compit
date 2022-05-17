#include <stdio.h>
#include <string.h>

#include "encode.h"
#include "decode.h"
#include "constants.h"

void decode_file(FILE *encoded) {
    ProbabilityDistribution pd;
    memset(pd.range, 0, sizeof(pd.range));

    unsigned char bitList[BUFFER_SIZE];

    for (int i = 0; i < BUFFER_SIZE; i++) {
        fread(&(bitList[i]), sizeof(unsigned char), 1, encoded);
        fread(&(pd.range[i]), sizeof(unsigned short), 1, encoded);
    }



    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%hx\t\t%hx\n", i, pd.range[i]);
    }
    
}