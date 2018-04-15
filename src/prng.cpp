#include "prng.hpp"
#include <math.h>
#include <gmpxx.h>

uint32_t * bbs_bignum()
{
    static uint32_t output[32] = { 0 };
    char *input_p = (char *)"284100283511244958272321698211826428679";
    char *input_q = (char *)"22582480853028265529707582510375286184991";
    char *input_r = (char *)"1387778780781445803070344004783973597184";
    bignum p(input_p, strlen(input_p));
    bignum q(input_q, strlen(input_q));
    bignum r(input_r, strlen(input_r));
    bignum n = p*q;
    bignum b("256", 3);
    bignum x;
    for(int i = 0; i < 32; i++)
    {
        r = bignum::modpow(r, 2, n);
        x = r % b;
        output[i] = x.toint();
    }

    return output;
}

void bbs()
{
    uint32_t out_put[32] = { 0 };

    mpz_class p("0xD5BBB96D30086EC484EBA3D7F9CAEB07");
    mpz_class q("0x425D2B9BFDB25B9CF6C416CC6E37B59C1F");
    mpz_class n = p*q;
    mpz_class x;
    mpz_class two("2"); 
    mpz_class b("256");
    mpz_class r;
    r = pow(5,56);
    for(int i = 0; i < 32; i++)
    {
        mpz_powm(r.get_mpz_t(),r.get_mpz_t(),two.get_mpz_t(),n.get_mpz_t());
        mpz_mod(x.get_mpz_t(),r.get_mpz_t(),b.get_mpz_t());
        out_put[i] = x.get_ui();          
    }
}

// void blum_mikali_bignum()
// {
//     uint32_t output[32] = { 0 };
//     char *input_p = (char *)"93466510612868436543809057926265637055082661966786875228460721852868821292003";
//     char *input_a = (char *)"41402113656871763270073938229168765778879686959780184368336806110280536326998";
//     char *input_t = (char *)"4096";
//     bignum p(input_p, strlen(input_p));
//     bignum a(input_a, strlen(input_a));
//     bignum T(input_t, strlen(input_t));
//     bignum c = (p - 1) / 2;
//     // c.output();
//     bignum b("256", 3);
//     bignum k;
//     for(int i = 0; i < 3; i++)
//     {
//         T = bignum_modpow(a, T, p);
//         // cout << "bignum output" << endl;
//         T.output();
//         // k  =  ( (T * b) / (p-1) );
//         // output[i] = k.toint();
//         // cout << output[i] << endl;
//     }
// }

void blum_mikali_byte()
{
    uint32_t output[32] = { 0 };
    mpz_class p("0xCEA42B987C44FA642D80AD9F51F10457690DEF10C83D0BC1BCEE12FC3B6093E3");
    mpz_class a("0x5B88C41246790891C095E2878880342E88C79974303BD0400B090FE38A688356");
    mpz_class one("1");
    mpz_class two("2");
    mpz_class T = pow(2,12);
    mpz_class c;
    c = (p-one)/2;
    mpz_class p_One;
    p_One = p-one;
    mpz_class b("256"), k;
    for(int i = 0; i < 3; i++)
    {
        // cout << T << endl;
        mpz_powm(T.get_mpz_t(),a.get_mpz_t(),T.get_mpz_t(),p.get_mpz_t());
        
        k  =  ((T * b)/(p-one));
        output[i] = k.get_ui();
        // cout << output[i] << endl;
    }
}