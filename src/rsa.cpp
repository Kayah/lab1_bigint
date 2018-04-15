#include "rsa.hpp"

rsa_ctx generate_keys(mpz_class &p, mpz_class &q, mpz_class &e)
{
    rsa_ctx result;
    mpz_class phi, p_, q_, d, n;
    n = p * q;
    p_ = p - 1;
    q_ = q - 1;
    phi = p_ * q_;
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
    result.d = d;
    result.n = n;
    result.e = e;
    return result;
}

void encrypt(mpz_class &message, mpz_class &encrypted, rsa_ctx &rsa)
{
    mpz_class e(rsa.e);
    mpz_class n(rsa.n);
    mpz_powm(encrypted.get_mpz_t(), message.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
}

void decrypt(mpz_class &encrypted, mpz_class &decrypted, rsa_ctx &rsa)
{
    mpz_class d (rsa.d);
    mpz_class n (rsa.n);
    mpz_powm(decrypted.get_mpz_t(), encrypted.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
}

void sign(mpz_class &message, mpz_class &signature, rsa_ctx &rsa)
{
    mpz_class d (rsa.d);
    mpz_class n (rsa.n);
    mpz_powm(signature.get_mpz_t(), message.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
}

bool verify(mpz_class &message, mpz_class &signature, rsa_ctx &rsa)
{
    mpz_class e (rsa.e);
    mpz_class n (rsa.n);
    mpz_class tmp;
    mpz_powm(tmp.get_mpz_t(), signature.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    
    if (mpz_cmp(tmp.get_mpz_t(), message.get_mpz_t()) == 0)
    {
        cout << "Signature verified.\n";
        return true;
    }

    cout << "Signature verification failed.\n";
    return false;
}