#include "bigintarithmetic.h"

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
