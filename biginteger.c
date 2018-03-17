/* 
** file: biginteger.h
*/
#include "biginteger.h"

void print_bigint(const bigint *n)
{
    int i;
	for (i=n->len-1; i>=0; i--)
		printf("%d", n->digits[i]);
	printf("\n");
}

void init_bigint(const char *input, int input_length, bigint *out)
{
    int i;
    int j;
    
    if (!input || (input_length == 0))
    {
        printf("Error, input == NULL, %s %s %d", __FILE__, __func__, __LINE__);
    }

    if (input_length > MAXINPUT)
    {
        printf("Error, input_length > MAXINPUT, %s %s %d", __FILE__, __func__, __LINE__);
    }
	
    for (i = 0, j = input_length-1; i < input_length; i++, j--)
    {
        out->digits[i] = input[j] - '0';
    }
	out->len = input_length;
}

static void sub(bigint *a, bigint *b, bigint *out, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i < len)
        {
            a->digits[i + 1]--;
            out->digits[i] += 10 + a->digits[i];
        }
        else
        {
            out->digits[i] += a->digits[i];
        }

        out->digits[i] -= b->digits[i];

        if ((out->digits[i] / 10) > 0)
        {
            out->digits[i + 1]++;
            out->digits[i] %= 10;
        }
    }
	out->len = len;   
}

void subtract_bigint(bigint *a, bigint *b, bigint *c)
{
	int k = 3;
    int len = a->len;
    if (a->len > b->len)
    {
        k = 1;
    }
    else if (b->len > a->len)
    {
        len = b->len;
        k = 2;
    }
    else
    {
        for (int i = 0; i < len;)
        {
            if (a->digits[i] > b->digits[i])
            {
                k = 1;
                break;
            }

            if (b->digits[i] > a->digits[i])
            {
                k = 2;
                break;
            }
        }
    }
	switch(k) {
		case 1:	
			sub(a, b, c, a->len);
			break;
		case 2:
			sub(b, a, c, b->len);
			break;
		case 3:
			c->len = 0;
			memset(c->digits, 0, MAXINPUT);
			break;
	}
}

void add_bigint(bigint *in0, bigint *in1)
{
    if (!in0 || !in1)
    {
        printf("Error, in0 == NULL || in1 == NULL || out == NULL, %s %s %d", \
                 __FILE__, __func__, __LINE__);
        return;
    }
	int len = max(in0->len, in1->len);
    
    for (int i = 0; i < len; i++)
    {
        in1->digits[i] += in0->digits[i];
        in1->digits[i+1] += (in1->digits[i] / 10);
        in1->digits[i] %= 10;
    }

    if (in1->digits[len -1] == 0)
        len--;
	in1->len = len;
}

void mult_bigint(bigint *a, bigint *b, bigint *c)
{
	int length = a->len + b->len;
 
    for (int ix = 0; ix < a->len; ix++)
        for (int jx = 0; jx <  b->len; jx++)
            c->digits[ix + jx] += a->digits[ix] * b->digits[jx];
    
    for (int ix = 0; ix < length; ix++)
    {
        c->digits[ix + 1] +=  c->digits[ix] / 10;
        c->digits[ix] %= 10;
    }
    
    // while (c->digits[length] == 0)
    //     length-- ;
    c->len = length;
}