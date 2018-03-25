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

int noOfDigit(long a)
{
    int n = 0;
    while(a > 0)
    {
        a /= 10;
        n++;
    }
    return n;
}

void sample(long x, long y, int n, int m)
{
    uint32_t linearConvolution[MAXINPUT];
    for (int i = 0; i < (n + m - 1); i++)
        linearConvolution[i] = 0;

    long p = x;
    for (int i = 0; i < m; i++)
    {
        x = p;
        for (int j = 0; j < n; j++)
        {
            linearConvolution[i + j] += (y % 10) * (x % 10);
            x /= 10;
        }
        y /= 10;
    }
    std::cout << "SAMPLE The Linear Convolution is: ( ";
    for (int i = (n + m - 2); i >= 0; i--)
    {
        std::cout << linearConvolution[i] << " ";
    }
    std::cout << ")\n";

    long product = 0;
    int nextCarry = 0, base = 1;
    
    for (int i = 0; i < n + m - 1; i++)
    {
        linearConvolution[i] += nextCarry;
        std::cout << base * (linearConvolution[i] % 10) << std::endl;
        // std::cout
        // product = product + (base * (linearConvolution[i] % 10));
        // nextCarry = linearConvolution[i] / 10;
        base *= 10;
    }
    // std::cout << "\nThe Product of the numbers is: " << product;

}
void set_bigint(bigint *x, bigint *y)
{
    for (int i = x->len - 1; i >= 0; i--)
        y->digits[i] = x->digits[i];
}
void schonhageStrassenMultiplication(bigint *x, bigint *y, int n, int m)
{
    uint64_t linearConvolution[MAXINPUT];
    for (int i = 0; i < (n + m - 1); i++)
        linearConvolution[i] = 0;
    bigint tmp;
    tmp.len = x->len;
    memset(tmp.digits, 0, MAXINPUT);
    set_bigint(x,&tmp);

    for (int i = 0; i < m; i++)
    {
        set_bigint(&tmp, x);
        for (int j = 0; j < n; j++)
        {
            linearConvolution[i + j] += (bii_mod(y, 10) * bii_mod(x, 10));
            bii_division(x, 10, 10);
        }
        bii_division(y, 10, 10);
    }
    std::cout << "TEST The Linear Convolution is: ( ";
    for (int i = (n + m - 2); i >= 0; i--)
    {
        std::cout << linearConvolution[i] << " ";
    }
    std::cout << ")\n";

    // long product = 0;
    static bigint product;
    bigint base;
    memset(product.digits, 0, MAXINPUT);
    product.len = MAXINPUT;
    memset(base.digits, 0, MAXINPUT);
    base.len = 1;
    base.digits[0] = 1;
    uint64_t nextCarry = 0;
    // uint32_t base = 1;
    tmp.len = base.len;
    memset(tmp.digits, 0, MAXINPUT);

    // for (int i = 0; i < n + m - 1; i++)
    // {
        // linearConvolution[i] += nextCarry;
        // product = product + (base * (linearConvolution[i] % 10));
        // nextCarry = linearConvolution[i] / 10;
        // base *= 10;
    // }
    set_bigint(&base, &tmp);
    for (int i = 0; i < 4; i++)
    {
        linearConvolution[i] += nextCarry;
        std::cout << "[ base " ;
        print_bigint(&base);
        std::cout << " tmp " ;
        print_bigint(&tmp);
        std::cout << " i = " << i <<"]"<<std::endl;
        set_bigint(&base, &tmp);
        bii_mult(&tmp, (linearConvolution[i] % 10));
        std::cout << " tmp after multiplication ";
        print_bigint(&tmp);
        // std::cout << linearConvolution[i] % 10 << std::endl;
        // add_bigint(&base, &product);
        // print_bigint(&product);
        // product = product + (base * (linearConvolution[i] % 10));
        // nextCarry = linearConvolution[i] / 10;
        // printf("\n");
        // set_bigint(&tmp, &base);
        // bii_mult(&base, 10);
        // print_bigint(&base);

    }
    // print_bigint(&product);
    
}
