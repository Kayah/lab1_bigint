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
    
    if (mpz_cmp(tmp.get_mpz_t(), message.get_mpz_t()) != 0)
    {
        cout << "Signature verification failed.\n";
        return false;
    }

    cout << "Signature verified successfuly.\n";
    return true;
}

secret_pair send_secret(rsa_ctx &rsa, mpz_class &b_n, mpz_class &b_e, mpz_class &secret)
{
    secret_pair out;
    mpz_class shared_secret, signature, shared_signature;
    if (mpz_cmp(rsa.n.get_mpz_t(), b_n.get_mpz_t()) > 0)
    {
        cout << "Inappropriate public key, please generate another one.\n";
        return out;
    }
    mpz_powm(shared_secret.get_mpz_t(), secret.get_mpz_t(), 
             b_e.get_mpz_t(), b_n.get_mpz_t());
    mpz_powm(signature.get_mpz_t(), secret.get_mpz_t(), 
             rsa.d.get_mpz_t(), rsa.n.get_mpz_t());
    mpz_powm(shared_signature.get_mpz_t(), signature.get_mpz_t(), 
             b_e.get_mpz_t(), b_n.get_mpz_t());
    cout << "shared secret = " << shared_secret << endl;
    cout << "signature = " << signature << endl;
    cout << "shared signature = " << shared_signature << endl;
    out.secret = shared_secret;
    out.signature = shared_signature;
    return out;
}

mpz_class recieve_key(rsa_ctx &rsa, mpz_class &public_key_B, mpz_class private_key_B, 
                      secret_pair &signed_message)
{
    mpz_class shared_secret, key, signature;

    if (mpz_cmp(public_key_B.get_mpz_t(), rsa.n.get_mpz_t()) < 0)
    {
        printf("Inappropriate public key, please generate another one.\n");
        return mpz_class(0);
    }
    mpz_powm(key.get_mpz_t(), signed_message.secret.get_mpz_t(), 
             private_key_B.get_mpz_t(), public_key_B.get_mpz_t());
    mpz_powm(signature.get_mpz_t(), signed_message.signature.get_mpz_t(), 
             private_key_B.get_mpz_t(), public_key_B.get_mpz_t());
    mpz_powm(shared_secret.get_mpz_t(), signature.get_mpz_t(), 
             rsa.e.get_mpz_t(), rsa.n.get_mpz_t());
    
    if (mpz_cmp(shared_secret.get_mpz_t(), key.get_mpz_t()) != 0)
    {
        cout << "Signature verification failed.\n";
        return mpz_class(0);
    }
    cout << "Signature verified.\n";
    cout << "signature = " << signature << endl;
    return signature;
}

