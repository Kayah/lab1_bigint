#ifndef BIGINTEGER_H
#define BIGINTEGER_H
/* 
** file: biginteger.hpp
*/
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

#define MAXINPUT 2048 /*maximum input size(bytes) of number*/
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

const int osn = 10;
class bignum
{  
public:
    bool isMinus;
    int amount;
    int digits[MAXINPUT];

    bignum() : amount(1), isMinus(false)
    {
        memset(digits, 0, MAXINPUT);
    }

    bignum(uint32_t i)
    {
        for (int i = 0; i < MAXINPUT; i ++)
            digits[i] = 0;
        amount = 1;
        isMinus = false;
        digits[amount - 1] = i;
    }

    bignum(const bignum &a): isMinus(a.isMinus), amount(a.amount)
    {
        memset(digits, 0, MAXINPUT);
        for (int i = 0; i < amount; i++)
            digits[i] = a.digits[i];
    }

    ~bignum()
    {}

    bignum(const char *input, int amount, bool isMinus = false):amount(amount), isMinus(isMinus)
    {
        memset(digits, 0, MAXINPUT);
        int i, j;
        for (i = 0, j = amount-1; i < amount; i++, j--)
            digits[i] = input[j] - '0';
	    this->amount = amount;
    }

    void input();
    void output();
    void LevelUp();
    uint64_t toint();

    static bignum modpow(bignum &b, uint32_t e, bignum &m)
    {
        bignum result(1);

        while(e > 0)
        {
            if ((e & 1) == 1)
            {
                result = (result * b) % m;
            }
            b = (b * b) % m;
            e >>= 1;
        }
        return result;
    }
   
    friend bignum operator /(const bignum &a, const bignum &b);
    friend bignum operator / (const bignum &a, const int &n);
    friend bignum operator *(const bignum &a, const bignum &b);
    friend bignum operator *(const bignum &a, const int &n);
    friend bignum operator -(const bignum &a, const bignum &b);
    friend bool operator == (const bignum &a, const bignum &b);
    friend bool operator == (const bignum &a, const int &n);
    friend bool operator > (const bignum &a, const bignum &b);
    friend bool operator < (const bignum &a, const bignum &b);
    friend bignum operator % (const bignum &a, const bignum &b);
    friend bignum operator + (const bignum &a, const bignum &b);
    friend bignum operator -(const bignum &a, const int b);
    friend bignum minus(const bignum &a, const bignum &b);
    friend bignum add(const bignum &a, const bignum &b);
};

bignum bignum_modpow(bignum &b, bignum &e, bignum &m);

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
void int_to_bigint(uint64_t s, bigint *n);
void copy_bigint(bigint *s, bigint *d);
void move_bigint(bigint *s, bigint *d);
void modpow_bigint(bigint *b, uint32_t e, bigint *m);
#endif // BIGINTEGER_H