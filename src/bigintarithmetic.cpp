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

// static void toom_cook_mult_helper(bigint *p_q_1, bigint *p_q_2,
//                                   bigint *p_q_8, bigint *mq2, 
//                                   bigint *mq1, bigint *mq0)
// {
//     bigint tmp, tmp2;
//     //p_1 = m0 - m1 + m2
//     copy_bigint(mq1, &tmp); //  save value of m1 due to bad implementation of sub :)
//     subtract_bigint(mq0, mq1, p_q_1);
//     move_bigint(&tmp, mq1); 
//     subtract_bigint(mq2, p_q_1, &tmp); // instead add, subtract was done 
//     copy_bigint(&tmp, p_q_1);         //due to bad implementation of sign add/sub
//     // print_bigint(&p_1);
//     //p_2 = m0 - 2m1 + 4m2
//     copy_bigint(mq1, &tmp);
//     bii_mult(&tmp, 2);
//     subtract_bigint(mq0, &tmp, p_q_2);
//     copy_bigint(mq2, &tmp);
//     bii_mult(&tmp, 4);
//     subtract_bigint(p_q_2, &tmp, &tmp2);
//     move_bigint(&tmp2, p_q_2);
//     //p_8 = m2
//     copy_bigint(mq2, p_q_8);

//     // print_bigint(p_q_1);
// }

void toom_cook_multiplication(char *inx, char *iny, bigint *out)
{
//     bigint m2, m1, m0, n2, n1, n0;
//     bigint p0, p1, p_1, p_2, p_8;
//     bigint q0, q1, q_1, q_2, q_8;
//     bigint f0, f1, f2, f3, f4;
//     bigint x, y;
//     bigint tmp, tmp2;
//     init_bigint(inx, strlen(inx) - 16, &m2);
//     init_bigint(inx + 6, strlen(inx) - 14, &m1);
//     init_bigint(inx + 14, strlen(inx) - 14, &m0);

//     init_bigint(iny, strlen(iny) - 16, &n2);
//     init_bigint(iny + 5, strlen(iny) - 13, &n1);
//     init_bigint(iny + 13, strlen(iny) - 13, &n0);
//     //p0 = m0
//     copy_bigint(&m0, &p0);
//     //p1 = m0+m1+m2
//     copy_bigint(&m1, &p1);
//     add_bigint(&m0, &p1);
//     add_bigint(&m2, &p1);
//     //p_1 = m0 - m1 + m2
//     toom_cook_mult_helper(&p_1, &p_2, &p_8, &m2, &m1, &m0); 
      
}

