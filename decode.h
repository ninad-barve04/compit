/**
 * @file decode.h
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DECODE_H
#define DECODE_H (1)

int decode_first_byte(FILE* decoded_file);
void decode_file(FILE *encoded, FILE *decoded);

#endif // DECODE_H
