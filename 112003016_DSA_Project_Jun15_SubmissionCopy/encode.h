/**
 * @file encode.h
 * @author Ninad Barve (barvenm20.comp@coep.ac.in)
 * @brief 
 * @version 1.0
 * @date 2022-06-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BIN_FILE_READ_H
#define BIN_FILE_READ_H (1)

#include "constants.h"
#include "index_table.h"

void encode_file(FILE *ip_fp, FILE *op_fp);
void write_bit(int bit, FILE *fp);

#endif // BIN_FILE_READ_H


