#include "bigintarithmetic.hpp"
typedef complex<double> base;

static void fft (vector<base> & a, bool invert) 
{
    int n = (int) a.size();
    if (n == 1)  return;

    vector<base> a0 (n/2),  a1 (n/2);
    for (int i=0, j=0; i<n; i+=2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    fft (a0, invert);
    fft (a1, invert);

    double ang = 2*PI/n * (invert ? -1 : 1);
    base w (1),  wn (cos(ang), sin(ang));
    for (int i=0; i<n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i+n/2] = a0[i] - w * a1[i];
        if (invert)
            a[i] /= 2,  a[i+n/2] /= 2;
        w *= wn;
    }
}

void fft_multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) 
{
    vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
   
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize (n);

    for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].real() + 0.5);

    int carry = 0;
    for (size_t i=0; i<n; ++i) {   
        res[i] += carry;
        carry = res[i] / 10;       
        res[i] %= 10;
    }
}

void karatsuba_multiplication(char *inx, char *iny, bigint *out)
{
    bigint in0, in1, res, res2;
    bigint s1, s2, s3, xl, xr, yl, yr;
    memset(res.digits, 0, MAXINPUT);
    memset(res2.digits, 0, MAXINPUT);
    init_bigint(inx, strlen(inx), &in0);
    init_bigint(iny, strlen(iny), &in1);
    int m = std::max(in0.len, in1.len);
    int m2 = m / 2; 
    init_bigint(inx, strlen(inx) - m2, &xl);
    init_bigint(iny, strlen(iny) - m2, &yl);
    init_bigint(inx + m2, strlen(inx) - m2, &xr);
    init_bigint(iny + m2, strlen(iny) - m2, &yr);
    // printf("Step 1:(a*c)\n");
    mult_bigint(&xl, &yl, &s1);
    // printf("Step 2:(b*d)\n");
    mult_bigint(&xr, &yr, &s2);
    // printf("Step 3:(a+b)*(c+d)\n");
    add_bigint(&xl, &xr);
    add_bigint(&yl, &yr);
    mult_bigint(&xr, &yr, &s3);
    // printf("Step 4: s3 -s2 -s1\n");
    subtract_bigint(&s3, &s2, &res);
    subtract_bigint(&res, &s1, &res2);
    tenpow(&s1, 2*m2);
    tenpow(&res2, m2);
    add_bigint(&s1, &res2);
    add_bigint(&res2, &s2);
	for (int i=s2.len-1; i>=0; i--)
        out->digits[i] = s2.digits[i];
    out->len = s2.len;
}

bignum toom_cook_multiplication(char *inx, char *iny)
{
    size_t inx_len = strlen(inx) / 3;
    size_t iny_len = strlen(iny) / 3;
    bignum x(inx, strlen(inx));
    bignum y(iny, strlen(iny));
    bignum out = x * y;
    bignum m2(inx, inx_len);
    bignum m1(inx + inx_len, inx_len);
    bignum m0(inx + (inx_len * 2), inx_len);
    
    bignum n2(iny, iny_len);
    bignum n1(iny + iny_len, iny_len);
    bignum n0(iny + (iny_len * 2), iny_len);
    //p0 = m0
    bignum p0 = m0;
    bignum q0 = n0;
    //p1 = m0+m1+m2
    bignum p1 = m0 + m1 + m2;
    bignum q1 = n0 + n1 + n2;
    // p_1 = m0 - m1 + m2
    bignum tmp = minus(m0, m1);
    bignum p_1 = add(tmp, m2);
    tmp = minus(n0, n1);
    bignum q_1 = add(tmp, n2);
    // p_2 = m0 - 2m1 + 4m2
    tmp = m1;
    tmp = tmp * 2;
    bignum p_2 = minus(m0, tmp);// + (m2 * 4);
    p_2 = add (p_2, (m2*4));
    tmp = n1;
    tmp = tmp * 2;
    bignum q_2 = minus(n0, tmp);
    q_2 = add (q_2, (n2 * 4));
    // p_8 = m2
    bignum p_8 = m2;
    bignum q_8 = n2;

    bignum r0 = p0 * q0;
    bignum r1 = p1 * q1;
    bignum r_1 = p_1 * q_1;
    bignum r_2 = p_2 * q_2;
    bignum r_8 = p_8 * q_8;

    bignum f0 = r0;
    bignum f4 = r_8;
    
    bignum f3 = (minus(r_2, r1)) / 3;
    bignum f1 = (minus(r1, r_1)) / 2;
    
    bignum f2 = minus(r_1, r0);
    tmp = (minus(f2, f3)) / 2;
    
    f3 = add(tmp, (r_8 * 2));
    tmp = minus(f1, f4);
    f2 = add(f2, tmp);
    f1 = minus(f1, f3);

    // f0.output();
    // cout << f0.isMinus << endl;
    // f1.output();
    // cout << f1.isMinus << endl;
    // f2.output();
    // cout << f2.isMinus << endl;
    // f3.output();
    // cout << f3.isMinus << endl;
    // f4.output();
    // cout << f4.isMinus << endl;
    
//                             24539087753298
//                      97685914820918
//            104845274440835
//        20040743684080
// 12193254061881
// 121932631246761163249178478656461057753298
    return out;
}

