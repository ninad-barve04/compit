/**
 * @file index_table.h
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef INDEX_TABLE_H
#define INDEX_TABLE_H (1)


typedef struct ProbabilityDistribution {
    unsigned int range[BUFFER_SIZE + 2];
    unsigned int frequency[BUFFER_SIZE + 2];
    unsigned char indexChar[NO_OF_SYMBOLS];
    int encodedChars[NO_OF_CHARS];

    unsigned long cumulative_prob;

    unsigned long total_count;

    int upper;
    int lower;

} ProbabilityDistribution;


void initialize_indexes(ProbabilityDistribution* pd);
void update_indexes(int byte, ProbabilityDistribution* pdistrib);

#endif
