/**
 * @file constants.c
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief Come of the constants required for the codec are defined here
 *
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <limits.h>

#include "constants.h"
 

#define ARRAY_LIMIT (UCHAR_MAX+1)

#define BUFFER_SIZE (256)

#define ENCODING_BUFFER (4)

const int CODE_VALUE = 16;

/* Maximum value of range */
const int MAX_RANGE_VALUE = 65535;

/* probability range should be in range of
   available to fit in N bit computation 2^(N-2)
   asumming 16 bit computation  = 16384
   */
const int MAX_FREQ = 16383;

/**
 * bound values for half interval, 1/4 interval and 3/4 interval
 */
const int FIRST_QUARTER_RANGE = (65535 / 4 + 1);
const int HALF_RANGE = (2 * (65535 / 4 + 1));
const int THIRD_QUARTER_RANGE = (3 * (65535 / 4 + 1));

 
const int EOF_SYMBOL = (257);
 