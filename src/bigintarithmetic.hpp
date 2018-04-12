#ifndef BIGINTARITHMETIC_HPP
#define BIGINTARITHMETIC_HPP
#include "biginteger.hpp"
#include <vector>
#include <complex>
#include <iostream>
#include "gtest/gtest.h"
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::complex;
using std::max;
#define PI 3.14
#define MAX_N 401
void karatsuba_multiplication(char *in0, char *in1, bigint *out);
void fft_multiply(const std::vector<int> & a, const std::vector<int> & b, std::vector<int> & res);
void toom_cook_multiplication(char *inx, char *iny, bigint *out);
#endif