#ifndef BIGINTARITHMETIC_H
#define BIGINTARITHMETIC_H
#include "biginteger.h"
#include "gtest/gtest.h"
void karatsuba_multiplication(char *in0, char *in1, bigint *out);
void schonhageStrassenMultiplication(bigint *x, bigint *y, int n, int m);
void sample(long x, long y, int n, int m);

int noOfDigit(long a);
#endif