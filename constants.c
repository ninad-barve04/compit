/**
 * @file constants.c
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <limits.h>

#include "constants.h"

/* probability range should be in range of
   available to fit in N bit computation 2^(N-2)
   asumming 16 bit computation  = 16384
   */
#define PROBABILITY_MAX 16384

#define ARRAY_LIMIT (UCHAR_MAX+1)


#define BUFFER_SIZE (256)

#define ENCODING_BUFFER (4)


const int CODE_VALUE = 16;
const int MAX_RANGE_VALUE = 65535;
const int MAX_FREQ = 16383;

const int FIRST_QUARTER_RANGE = (65535 / 4 + 1);
const int HALF_RANGE = (2 * (65535 / 4 + 1));
const int THIRD_QUARTER_RANGE = (3 * (65535 / 4 + 1));

 
const int EOF_SYMBOL = (257);
 