#include "prng.hpp"
#include <math.h>
#include <gmpxx.h>
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

    // uint32_t x = 0;
    // bigint p, q, n, r;
    // char *input_p = (char *)"284100283511244958272321698211826428679";
    // char *input_q = (char *)"22582480853028265529707582510375286184991";
    // char *input_r = (char *)"1387778780781445675529539585113525390625";
    // init_bigint(input_p, strlen(input_p), &p);
    // init_bigint(input_q, strlen(input_q), &q);
    // init_bigint(input_r, strlen(input_r), &r);
    // mult_bigint(&p, &q, &n);
    //r = pow(5,56); //TODO: add pow function

    for(int i = 0; i < 32; i++)
    {

        mpz_powm(r.get_mpz_t(),r.get_mpz_t(),two.get_mpz_t(),n.get_mpz_t());
        mpz_mod(x.get_mpz_t(),r.get_mpz_t(),b.get_mpz_t());
        cout << x.get_ui() << endl;
        out_put[i] = x.get_ui();      

        // modpow_bigint(&r, 2, &n);
        // x = bii_mod(&r, 256);
      
        // cout << x << endl;
    
    }
}