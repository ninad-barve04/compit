/**
 * @file constants.h
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef CONSTANTS_H
#define CONSTANTS_H (1)

#include <limits.h>

/* 
 * probability range should be in range of
 * available to fit in N bit computation 2^(N-2)
 * asumming 16 bit computation  = 16384
 */
#define PROBABILITY_MAX 16384

#define ARRAY_LIMIT (UCHAR_MAX+1)


#define BUFFER_SIZE (256)

#define ENCODING_BUFFER (4)
#define NO_OF_CHARS (256)
#define NO_OF_SYMBOLS (257)


extern const int CODE_VALUE;
extern const int MAX_RANGE_VALUE;
extern const int MAX_FREQ;

extern const int FIRST_QUARTER_RANGE;
extern const int HALF_RANGE;
extern const int THIRD_QUARTER_RANGE;


extern const int EOF_SYMBOL;


#endif // CONSTANTS_H
