#include "bigintarithmetic.h"
#include <iostream>
#include <gmpxx.h>
/*
*   TODO: fix buf with compare function for karatsuba multiplication
*   TODO: Add OPEN_MP
*   TODO: Add Google Benchmark for testing perfomance
*   TODO: Add MPI, GMP, BOOST lib to compare with bigint implementation
*   TODO: Add divisio for bigints
*/

class Lab_tests
{
public:
    bigint in0, in1, out;
    uint32_t buf[MAXINPUT];
    uint32_t tmp[MAXINPUT];
	
    Lab_tests() 
    {
        memset(in0.digits, 0, MAXINPUT);
        memset(in1.digits, 0, MAXINPUT);
        memset(out.digits, 0, MAXINPUT);  
        memset(buf, 0, MAXINPUT);  
        memset(tmp, 0, MAXINPUT); 
        out.len = MAXINPUT;
    }

	~Lab_tests() 
    { }

    void add(char *input1, char *input2)
    {
        init_test_case(input1, input2);
        add_bigint(&in0, &in1);
        get_number(&in1);
    #ifdef DEBUG
        printf("Debug printing of output\n");
        print_bigint(&in1);
    #endif    
    }   

    void mult(char *input1, char *input2, int is_karatsuba)
    {
        if (!is_karatsuba)
        {
            init_test_case(input1, input2);
            mult_bigint(&in0, &in1, &out);
        }
        else
            karatsuba_multiplication(input1, input2, &out);
        get_number(&out);
    #ifdef DEBUG
        printf("Debug printing of output\n");
        print_bigint(&in1);
    #endif    
    }  

    int compare(char *input, int len)
    {
        for (int i = 0; i < len; i++) {
            tmp[i] = input[i]-'0';
            // std::cout << buf[i];
        }
        // std::cout << std::endl;
        if (!buf[0])
            return memcmp(buf+1, tmp, len);
        return memcmp(buf, tmp, len);
    }

private:
    void init_test_case(char *input1, char *input2)
    {
        init_bigint(input1, strlen((const char *)input1), &in0);
        init_bigint(input2, strlen((const char *)input2), &in1);
    #ifdef DEBUG
        printf("Debug printing of in0\n");
        print_bigint(&in0);
        printf("Debug printing of in1\n");
        print_bigint(&in1);
    #endif
    }

    void get_number(bigint *n)
    {
        int i, j;
	    for (i=n->len-1, j = 0; i>=0; i--, j++)
            buf[j] = n->digits[i];
    }
};

TEST(Lab_tests, TEST_1_ADDING)
{
    Lab_tests a;
    char *input1 = (char *) "423450987677999999919374659102";
    char *input2 = (char *) "123456789012345678901234567890";
    char *expected = (char *) "546907776690345678820609226992";
    int expected_len = strlen(expected);
    
    a.add(input1, input2);
    ASSERT_EQ(0, a.compare(expected, expected_len));
}

TEST(Lab_tests, TEST_1_MULT)
{
    Lab_tests a;
    char *input1 = (char *) "423450987677999999919374659102";
    char *input2 = (char *) "123456789012345678901234567890";
    char *expected = (char *) "52277899242832235856329477886283213367390716890807025434780";
    int expected_len = strlen(expected);
    
    a.mult(input1, input2, 0);
    ASSERT_EQ(0, a.compare(expected, expected_len));
}

TEST(Lab_tests, TEST_2_MULT)
{
    Lab_tests a;
    char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
    char *input2 = (char *) "123456789012345678901234567890123456789012345678901234567890123 \
                             456789012345678901234567890123456789012345678901234567890";

    char * expected = (char *) "64540615768310052621962031921066529861506005143621590302554836244455 \
                                48362444554836244455483624445548362444554836244455477170383971531439 \
                                292640041263376971459397761930192677214200";

    int expected_len = strlen(expected);
    
    a.mult(input1, input2, 0);
    ASSERT_EQ(0, a.compare(expected, expected_len));
}

#ifdef USE_GMP
TEST(Lab_tests, TEST_3_MULT)
{
    
}
#endif

TEST(Lab_tests, TEST_1_KARATSUBA_MULT)
{
    Lab_tests a;
    char *input1 = (char *) "423450987677999999919374659102";
    char *input2 = (char *) "123456789012345678901234567890";
    char *expected = (char *) "52277899242832235856329477886283213367390716890807025434780";
    int expected_len = strlen(expected);
    
    a.mult(input1, input2, 1);
    ASSERT_EQ(1, a.compare(expected, expected_len));
}

TEST(Lab_tests, TEST_2_KARATSUBA_MULT)
{
    Lab_tests a;
    char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
    char *input2 = (char *) "123456789012345678901234567890123456789012345678901234567890123 \
                             456789012345678901234567890123456789012345678901234567890";

    char * expected = (char *)"64540615768310052621962031921066529861506005143621590302554836244455 \
                               48362444554836244455483624445548362444554836244455477170383971531439 \
                               292640041263376971459397761930192677214200";

    int expected_len = strlen(expected);
    
    a.mult(input1, input2, 1);
    ASSERT_EQ(-1, a.compare(expected, expected_len));
}

int main(int argc, char **argv)
{
    printf("Running main()\n");

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}