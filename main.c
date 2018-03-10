#include "biginteger.h"
int 
main()
{
    bigint output;
    bigint output1;
    bigint output2;
    //char *input1 = (char *) "4234509876779999999";
    // char *input1 = (char *) "97";
    char *input1 = (char *) "123456789012345678901234567890";
    char *input2 = (char *) "123456789012345678901234567890";
    // char *input2 = (char *) "12";
    memset(output2.digits, 0, MAXINPUT);
    memset(output1.digits, 0, MAXINPUT);
    memset(output.digits, 0, MAXINPUT);
    init_bigint(input1, strlen(input1), 1, &output);
    init_bigint(input2, strlen(input2), 1, &output1);
    add_bigint(&output,&output1,&output2);
    print_bigint(&output2);
    memset(output2.digits, 0, MAXINPUT);
    output2.lastdigit = 0;
    mult_bigint(&output, &output1, &output2);
    print_bigint(&output2);
    memset(output2.digits, 0, MAXINPUT);
    subtract_bigint(&output, &output1, &output2);
    print_bigint(&output2);
    return 0;
}