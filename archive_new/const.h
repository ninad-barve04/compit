#include <limits.h>

/* probability range should be in range of
   available to fit in N bit computation 2^(N-2)
   asumming 16 bit computation  = 16384
   */
#define PROBABILITY_MAX 16384

#define ARRAY_LIMIT (UCHAR_MAX+1)
