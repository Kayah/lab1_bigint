#include "bigintarithmetic.h"

void
karatsuba_multiplication(char *inx, 
                         char *iny, 
                         bigint *out)
{
    bigint in0, in1, res;
    bigint s1, s2, xl, xr, yl, yr;
    memset(res.digits, 0, MAXINPUT);
    init_bigint(inx, strlen(inx), &in0);
    init_bigint(iny, strlen(iny), &in1);
    // mult_bigint(&in0, &in1, &res);
    // print_bigint(&in0);
    // print_bigint(&in1);
    // print_bigint(&res);
    int m = max(in0.len, in1.len);
    int m2 = m / 2; 
    printf("%zu\n", strlen(inx)-m2);
    init_bigint(inx, strlen(inx) - m2, &xl);
    init_bigint(iny, strlen(iny) - m2, &yl);
    print_bigint(&xl);
    print_bigint(&yl);
}