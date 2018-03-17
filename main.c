#include "bigintarithmetic.h"

int main()
{
    bigint in0, in1, out;
    memset(out.digits, 0, MAXINPUT);
    out.len = MAXINPUT;
    // char *input1 = (char *) "423450987677999999919374659102";
    char *input1 = (char *) "88";
    // char *input1 = (char *) "123456789012345678901234567890";
    // char *input2 = (char *) "123456789012345678901234567890";
    char *input2 = (char *) "44";
    // char *input1 = (char*)"123456789012345";
    // char *input2 = (char*)"123456789012345";
    // karatsuba_multiplication(input1, input2, &out);
    init_bigint(input1, strlen((const char *)input1), &in0);
    init_bigint(input2, strlen((const char *)input2), &in1);

    print_bigint(&in0);
    print_bigint(&in1);
    bii_division(&in0, 44, 10);
    print_bigint(&in0);
    
    // init_bigint(input2, strlen((const char *)input2), &in1);
    // print_bigint(&in0);
    // int base = base_calc(&in0);
    // printf("%d\n", base);
    // print_bigint(&in1);
    // add_bigint(&in0, &in1);
    // subtract_bigint(&in0, &in1, &out);
    // int k = sign_check(&in0, &in1);
    // printf("%d\n", k);
    // if (k == 2) sub(&in1, &in0, &out, 30);
    // if (k == 2) sub(&in1, &in0, &out, 30);
    // mult_bigint(&in0, &in1, &out);
    // print_bigint(&out);
    return 0;
}