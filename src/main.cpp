#include "bigintarithmetic.hpp"
#include <iostream>
#include <gmpxx.h>
enum mult_type {SCHOOL_MULT = 0, KARATSUBA_MULT = 1, FFT_MULT = 2};
class Lab_tests
{
public:
    bigint in0, in1, out;
    uint32_t buf[MAXINPUT];
    uint32_t tmp[MAXINPUT];
	vector<int> a, b, res;
    Lab_tests() 
    {
        memset(in0.digits, 0, MAXINPUT);
        memset(in1.digits, 0, MAXINPUT);
        memset(out.digits, 0, MAXINPUT);  
        memset(buf, 0, MAXINPUT);  
        memset(tmp, 0, MAXINPUT); 
        out.len = MAXINPUT;
    }

    Lab_tests(vector<int> a, vector<int> b): a(a), b(b)
    {
        Lab_tests();
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

    void mult(char *input1, char *input2, int mult_type)
    {
        if (mult_type != FFT_MULT && !input1 && !input2)
        {
            cout << "Parameters must be provided !" << endl;
            return;
        }
        switch(mult_type)
        {
            case KARATSUBA_MULT:
            karatsuba_multiplication(input1, input2, &out);            
            break;

            case SCHOOL_MULT:
            init_test_case(input1, input2);
            mult_bigint(&in0, &in1, &out);
            break;

            case FFT_MULT:
            fft_multiply(a, b, res);
            for (long i = res.size()-27; i >= 0; i--) // shifts result on 27 bytes to get readeble result, FIX IT !
                cout << res[i];
            cout << endl;
            break;
        }
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

    uint64_t mod(char *input, int p)
    {
        init_bigint(input, strlen((const char *)input), &in0);
        return bii_mod(&in0, p);
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

// TEST(Lab_tests, TEST_1_ADDING)
// {
//     Lab_tests a;
//     char *input1 = (char *) "423450987677999999919374659102";
//     char *input2 = (char *) "123456789012345678901234567890";
//     char *expected = (char *) "546907776690345678820609226992";
//     int expected_len = strlen(expected);
    
//     a.add(input1, input2);
//     ASSERT_EQ(0, a.compare(expected, expected_len));
// }

// TEST(Lab_tests, TEST_1_MULT)
// {
//     Lab_tests a;
//     char *input1 = (char *) "423450987677999999919374659102";
//     char *input2 = (char *) "123456789012345678901234567890";
//     char *expected = (char *) "52277899242832235856329477886283213367390716890807025434780";
//     int expected_len = strlen(expected);
    
//     a.mult(input1, input2, 0);
//     ASSERT_EQ(0, a.compare(expected, expected_len));
// }

// TEST(Lab_tests, TEST_2_MULT)
// {
//     Lab_tests a;
//     char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
//     char *input2 = (char *) "123456789012345678901234567890123456789012345678901234567890123 \
//                              456789012345678901234567890123456789012345678901234567890";

//     char * expected = (char *) "64540615768310052621962031921066529861506005143621590302554836244455 \
//                                 48362444554836244455483624445548362444554836244455477170383971531439 \
//                                 292640041263376971459397761930192677214200";

//     int expected_len = strlen(expected);
    
//     a.mult(input1, input2, 0);
//     ASSERT_EQ(0, a.compare(expected, expected_len));
// }

TEST(Lab_tests, TEST_1_FFT_MULT)
{
    /*5218765431987654321 * 5218765431987654321*/
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3, 4, 5, 6, 7, 8, 1, 2, 5};
    vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3, 4, 5, 6, 7, 8, 1, 2, 5};
    Lab_tests test(a, b);
    test.mult(NULL, NULL, FFT_MULT);
}

// TEST(Lab_tests, TEST_1_MOD)
// {
//     Lab_tests a;
//     char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
//     uint64_t ret = a.mod(input1, 11);
//     ASSERT_EQ(7, ret);
// }


// #ifdef USE_GMP
// TEST(Lab_tests, TEST_3_MULT_GMP)
// {
    
// }
// #endif

// TEST(Lab_tests, TEST_4_MULT_OPENSSL)
// {

// }

// TEST(Lab_tests, TEST_1_KARATSUBA_MULT)
// {
//     Lab_tests a;
//     char *input1 = (char *) "423450987677999999919374659102";
//     char *input2 = (char *) "123456789012345678901234567890";
//     char *expected = (char *) "52277899242832235856329477886283213367390716890807025434780";
//     int expected_len = strlen(expected);
    
//     a.mult(input1, input2, 1);
//     ASSERT_EQ(1, a.compare(expected, expected_len));
// }

// TEST(Lab_tests, TEST_2_KARATSUBA_MULT)
// {
//     Lab_tests a;
//     char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
//     char *input2 = (char *) "123456789012345678901234567890123456789012345678901234567890123 \
//                              456789012345678901234567890123456789012345678901234567890";

//     char * expected = (char *)"64540615768310052621962031921066529861506005143621590302554836244455 \
//                                48362444554836244455483624445548362444554836244455477170383971531439 \
//                                292640041263376971459397761930192677214200";

//     int expected_len = strlen(expected);
    
//     a.mult(input1, input2, 1);
//     ASSERT_EQ(-1, a.compare(expected, expected_len));
// }

int main(int argc, char **argv)
{
    printf("Running main()\n");

	testing::InitGoogleTest(&argc, argv);
    
	return RUN_ALL_TESTS();
}