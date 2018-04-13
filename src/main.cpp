#include "bigintarithmetic.hpp"
#include <iostream>
#include <openssl/bn.h>
#include "prg.hpp"
#ifdef USE_GMP
#include <gmpxx.h>
#endif
enum mult_type {SCHOOL_MULT = 0, KARATSUBA_MULT = 1, FFT_MULT = 2, TOOM_COOK_MULT = 3};
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

    void mult (char *input1, char *input2, int mult_type)
    {
        bignum out0;
        mult(input1, input2, mult_type, out0);
    }
    void mult(char *input1, char *input2, int mult_type, bignum &out0)
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
        #ifdef DEBUG    
            for (long i = res.size()-27; i >= 0; i--) // shifts result on 27 bytes to get readeble result, FIX IT !
                cout << res[i];
            cout << endl;
        #endif
            return;

            case TOOM_COOK_MULT:
            out0 = toom_cook_multiplication(input1, input2);
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

TEST(Lab_tests, TEST_SCHOOL_ADDING)
{
    Lab_tests a;
    char *input1 = (char *) "423450987677999999919374659102";
    char *input2 = (char *) "123456789012345678901234567890";
    char *expected = (char *) "546907776690345678820609226992";
    int expected_len = strlen(expected);
    
    a.add(input1, input2);
    ASSERT_EQ(0, a.compare(expected, expected_len));
}

TEST(Lab_tests, TEST_SCHOOL_MULT_1)
{
    Lab_tests a;
    char *input1 = (char *) "423450987677999999919374659102";
    char *input2 = (char *) "123456789012345678901234567890";
    char *expected = (char *) "52277899242832235856329477886283213367390716890807025434780";
    int expected_len = strlen(expected);
    
    a.mult(input1, input2, 0);
    ASSERT_EQ(0, a.compare(expected, expected_len));
}

TEST(Lab_tests, TEST_SCHOOL_MULT_2)
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

TEST(Lab_tests, TEST_FFT_MULT)
{
    /*5218765431987654321 * 5218765431987654321*/
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3, 4, 5, 6, 7, 8, 1, 2, 5};
    vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3, 4, 5, 6, 7, 8, 1, 2, 5};
    Lab_tests test(a, b);
    test.mult(NULL, NULL, FFT_MULT);
}

TEST(Lab_tests, TEST_TOOM_COOK_MULT)
{
    Lab_tests test;          
    char *input1 = (char *) "123456789012345678901";
    char *input2 = (char *) "987654321987654321098";
    bignum out;
    test.mult(input1, input2, TOOM_COOK_MULT, out);
    out.output();
}

TEST(Lab_tests, TEST_MOD)
{
    Lab_tests a;
    char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
    uint64_t ret = a.mod(input1, 11);
    ASSERT_EQ(7, ret);
}

TEST(Lab_tests, TEST_BIGNUM)
{
    char *input1 = (char *) "52277899242832235856329477886283213367390716890807025434780";
    char *input2 = (char *) "987654321987654321098";
    bignum a(input1, strlen(input1));
    bignum b(input2, strlen(input2));
    a.output();
    b.output();
    bignum res = a % b;
    res.output();
}

#ifdef USE_GMP
TEST(Lab_tests, TEST_MULT_GMP)
{

}
#endif

TEST(Lab_tests, TEST_MULT_OPENSSL)
{
    BIGNUM *bn1 = NULL;
	BIGNUM *bn2 = NULL;
	BIGNUM *result = BN_new();
	BN_CTX *bn_ctx = BN_CTX_new();
	
	BN_dec2bn(&bn1, "423450987677999999919374659102");
	BN_dec2bn(&bn2, "123456789012345678901234567890");
		
	BN_mul(result, bn2, bn1, bn_ctx);
#ifdef DEBUG    
	printf("Result is %s\n", BN_bn2dec(result));
#endif
	BN_free(bn1);
	BN_free(bn2);
	BN_free(result);
    BN_CTX_free(bn_ctx);
}

TEST(Lab_tests, TEST_ADD_OPENSSL)
{
    BIGNUM *bn1 = NULL;
	BIGNUM *bn2 = NULL;
	BIGNUM *result = BN_new();
	BN_CTX *bn_ctx = BN_CTX_new();
	
	BN_dec2bn(&bn1, "423450987677999999919374659102");
	BN_dec2bn(&bn2, "123456789012345678901234567890");
		
	BN_add(result, bn2, bn1);
#ifdef DEBUG
	printf("Result is %s\n", BN_bn2dec(result));
#endif		
	BN_free(bn1);
	BN_free(bn2);
	BN_free(result);
    BN_CTX_free(bn_ctx);
}

TEST(Lab_tests, DISABLED_TEST_KARATSUBA_MULT_1)
{
    Lab_tests a;
    char *input1 = (char *) "423450987677999999919374659102";
    char *input2 = (char *) "123456789012345678901234567890";
    char *expected = (char *) "52277899242832235856329477886283213367390716890807025434780";
    int expected_len = strlen(expected);
    
    a.mult(input1, input2, 1);
    ASSERT_EQ(2, a.compare(expected, expected_len));
}

TEST(Lab_tests, DISABLED_TEST_KARATSUBA_MULT_2)
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
    ASSERT_EQ(-2, a.compare(expected, expected_len));
}

int main(int argc, char **argv)
{
    printf("Running main()\n");
    // bbs();
	testing::InitGoogleTest(&argc, argv);
    
	return RUN_ALL_TESTS();
}