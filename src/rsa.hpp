#ifndef RSA_HPP
#define RSA_HPP
#include "biginteger.hpp"
#include <math.h>
#include <gmpxx.h>
using std::cout;
using std::endl;

struct rsa_ctx 
{
    mpz_class e; 
    mpz_class n; 
    mpz_class d;
    mpz_class p;
    mpz_class q;
};

rsa_ctx generate_keys(mpz_class &p, mpz_class &q, mpz_class &e);
void encrypt(mpz_class &message, mpz_class &encrypted, rsa_ctx &rsa);
void decrypt(mpz_class &encrypted, mpz_class &decrypted, rsa_ctx &rsa);
void sign(mpz_class &message, mpz_class &signature, rsa_ctx &rsa);
bool verify(mpz_class &message, mpz_class &signature, rsa_ctx &rsa);
#endif