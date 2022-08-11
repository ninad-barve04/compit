/**
 * @file index_table.c
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>
#include "constants.h"
#include "index_table.h"


void initialize_indexes(ProbabilityDistribution* pd)
{
    int i = 0;
    for (i = 0; i <= NO_OF_SYMBOLS; i++) {
        (*pd).frequency[i] = 1;
        (*pd).range[i] = NO_OF_SYMBOLS - i;
    }
    (*pd).frequency[0] = 0;
    for (i = 0; i < NO_OF_CHARS; i++)
    {
        (*pd).encodedChars[i] = i + 1;
        (*pd).indexChar[i + 1] = i;
    }
    (*pd).indexChar[0] = 0;
}


void update_indexes(int byte, ProbabilityDistribution* pdistrib)
{


    int i;
    int d = 0;
    if ((*pdistrib).range[0] == MAX_FREQ)
    {
        d = 0;
        int cum = 0;
        for (i = NO_OF_SYMBOLS; i >= 0; i--)
        {
            (*pdistrib).frequency[i] = ((*pdistrib).frequency[i] + 1) / 2;
            (*pdistrib).range[i] = cum;
            cum += (*pdistrib).frequency[i];
        }
    }

    for (i = byte; (*pdistrib).frequency[i] == (*pdistrib).frequency[i - 1]; i--);
    if (i < byte)
    {
        int ch_i, ch_symbol;
        ch_i = (*pdistrib).indexChar[i];
        ch_symbol = (*pdistrib).indexChar[byte];
        (*pdistrib).indexChar[i] = ch_symbol;
        (*pdistrib).indexChar[byte] = ch_i;
        (*pdistrib).encodedChars[ch_i] = byte;
        (*pdistrib).encodedChars[ch_symbol] = i;
    }
    (*pdistrib).frequency[i]++;
    while (i > 0)
    {
        i--;
        (*pdistrib).range[i]++;
    }
}