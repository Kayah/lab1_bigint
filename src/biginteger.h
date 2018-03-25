#ifndef BIGINTEGER_H
#define BIGINTEGER_H
/* 
** file: biginteger.h
*/
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

#define MAXINPUT 512 /*maximum input size(bytes) of number*/
#define PLUS		1
#define MINUS		-1
/**
 *  bigint structure
 *  digits: array of int, contains input number
 *  signbit: indicates negative or positive sign of the number
 *  lastdigit: indicates number size
 */
typedef struct
{
    uint32_t digits[MAXINPUT];
    int signbit;
    int len;
}bigint;

/*x = x1 * B^m + x0;*/
typedef struct
{
    uint32_t digits[MAXINPUT];
    uint32_t x1[MAXINPUT/4];
    uint32_t x0[MAXINPUT/4];
    int len;
    int base;
    int m;
}factored_num;

int base_calc(bigint *in);
void tenpow(bigint *n, int d);

/**
 * init_bigint function, initialize bigint with user input
 * input: string with provided big number
 * input_length: input length of provided input
 * signbit: indicates negative or positive sign of the number(1 or -1)
 * out: output bigint, should be provided from caller
 */
void init_bigint(const char *input, int input_length, bigint *out);

/**
 * add_bigint function, add two big numbers
 * in0: input bigint
 * in1: input bigint, will contains output
 */
void add_bigint(bigint *in0, bigint *in1);

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

/**
 * bii_division function, multiply big number and scalar b
 * in0: input bigint
 * b: 2^64-1 number
 * base: base of b 
 * out: output put in in0
 */
void bii_division(bigint *n, long long b, long long base);

uint64_t bii_mod(bigint *in0, int p);
void bii_mult(bigint *in0, uint64_t b);
#endif // BIGINTEGER_H