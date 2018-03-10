#ifndef BIGINTEGER_H
#define BIGINTEGER_H
/* 
** file: biginteger.h
*/
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXINPUT 512 /*maximum input size(bytes) of number*/

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
       _a > _b ? _a : _b;})

#define PLUS    1
#define MINUS  -1

/**
 *  bigint structure
 *  digits: array of int, contains input number
 *  signbit: indicates negative or positive sign of the number
 *  lastdigit: indicates number size
 */
typedef struct
{
    int digits[MAXINPUT];
    int signbit;
    int lastdigit;

}bigint;

/**
 * init_bigint function, initialize bigint with user input
 * input: string with provided big number
 * input_length: input length of provided input
 * signbit: indicates negative or positive sign of the number(1 or -1)
 * out: output bigint, should be provided from caller
 */
void init_bigint(const char *input, uint32_t input_length, int signbit, bigint *out);

/**
 * add_bigint function, add two big numbers
 * in0: input bigint
 * in1: input bigint
 * out: output bigint, should be provided by caller
 */
void add_bigint(bigint *in0, bigint *in1, bigint *out);

/**
 * mult_bigint function, multiply two big numbers
 * in0: input bigint
 * in1: input bigint
 * out: output bigint, should be provided by caller
 */
void mult_bigint(bigint *in0, bigint *in1, bigint *out);

/**
 * print_bigint, print bigint's digits field
 * input: input bigint
 */
void print_bigint(const bigint *input);

/**
 * subtract_bigint function, subtracts two big numbers
 * in0: input bigint
 * in1: input bigint
 * out: output bigint, should be provided by caller
 */
void subtract_bigint(bigint *in0, bigint *in1, bigint *out);
#endif // BIGINTEGER_H