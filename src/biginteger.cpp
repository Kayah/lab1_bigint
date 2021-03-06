/* 
** file: biginteger.hpp
*/
#include "biginteger.hpp"
using std::cout;
using std::endl;
void print_bigint(const bigint *n)
{
    int i;
	for (i=n->len-1; i>=0; i--)
		printf("%d", n->digits[i]);
	printf("\n");
}

void zero_justify(bigint *n)
{
	if ((n->digits == 0) && (n->digits[0] == 0))
    	n->signbit = PLUS;
}

void int_to_bigint(uint64_t s, bigint *n)
{
	int i;				
	int t = 0;
    memset(n->digits, 0, MAXINPUT);
	for (i = 0; i < MAXINPUT; i++) n->digits[i] =  0;
	t = s;
    n->len = 0;
	while (t > 0) {
		n->digits[ n->len ] = (t % 10);
		t = t / 10;
        ++n->len;
	}
}

void copy_bigint(bigint *s, bigint *d)
{
	memset(d->digits, 0, MAXINPUT);
    d->len = s->len;
    for (int i = d->len; i >= 0; i--)
        d->digits[i] = s->digits[i];
    d->signbit = s->signbit;
}

void move_bigint(bigint *s, bigint *d)
{
    copy_bigint(s, d);
	memset(s->digits, 0, MAXINPUT);
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
    out->signbit = PLUS;
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
        for (int i = 0; i < len; i++)
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
            c->signbit = PLUS;
			break;
		case 2:
			sub(b, a, c, b->len);
            c->signbit = MINUS;
			break;
		case 3:
			c->len = 0;
			memset(c->digits, 0, MAXINPUT);
            c->signbit = PLUS;
			break;
	}
}

void add_bigint(bigint *in0, bigint *in1)
{
    static bigint out;

    if (!in0 || !in1)
    {
        printf("Error, in0 == NULL || in1 == NULL || out == NULL, %s %s %d", \
                 __FILE__, __func__, __LINE__);
        return;
    }

    memset(out.digits, 0, MAXINPUT);
    out.len = in0->len;

	int len = std::max(in0->len, in1->len);

    for (int i = 0; i < len; i++)
    {
        in1->digits[i] += in0->digits[i];
        in1->digits[i+1] += (in1->digits[i] / 10);
        in1->digits[i] %= 10;
    }

    if (in1->digits[len -1] == 0)
        len--;
	in1->len = len+1;
}

void mult_bigint(bigint *a, bigint *b, bigint *c)
{
	int length = a->len + b->len;
    for (int i = 0; i < a->len; i++)
        for (int j = 0; j <  b->len; j++)
            c->digits[i + j] += a->digits[i] * b->digits[j];
    
    for (int i = 0; i < length; i++)
    {
        c->digits[i + 1] +=  c->digits[i] / 10;
        c->digits[i] %= 10;
    }
    
    // while (c->digits[length] == 0)
    //     length-- ;
    c->len = length;
}

int base_calc(bigint *in0)
{
    int i = 0;
    int base = 0;

    for (i = in0->len; i > 0; i--)
    {
        if (i % 3 == 0)
            base++;
    }
    return base;
}

void tenpow(bigint *n, int d)
{
	int i;

    if ((n->len == 0) && (n->digits[0] == 0)) return;

	for (i=n->len; i>=0; i--)
		n->digits[i+d] = n->digits[i];

	for (i=0; i<d; i++) n->digits[i] = 0;

	n->len = n->len + d;
}

void LevelUp(bigint *n)
{
  for (int i = n->len ; i >= 1 ;i--)
    n->digits[i] = n->digits[i-1];
  if (n->digits[n->len])
    n->len++;
}

void div_bigint (const bigint *a,  bigint *b)
{

} 

void bii_division(bigint *in0, long long in_b, long long in_base)
{
    int carry = 0;
    int base = in_base;
    int b = in_b;
    for (int i = in0->len - 1; i >= 0; --i)
    {
        long long cur = in0->digits[i] + carry * 1ll * base;
        in0->digits[i] = (int)(cur / b);
        carry = (int)(cur % b);
    }
}

uint64_t bii_mod(bigint *in0, int p)
{
    uint64_t ret = 0;
    int j = 0;
    for (int i = 0, j = in0->len-1; i < in0->len; i++, j--)
        ret = (ret * 10 + in0->digits[j]) % p;
    return ret;
}

void bii_mult(bigint *in0, uint64_t b)
{
    int carry = 0;
    uint32_t i;
    // print_bigint(in0);
    // std::cout << "!!!!\n";
    // for (int i = 0; i < MAXINPUT; i++)
    //     std::cout << in0->digits[i];
    // std::cout<<" mult on " << b << std::endl;
    for (i = 0; i < in0->len || carry; i++)
    {
        uint64_t cur = carry + in0->digits[i] * 1ll * b;
        in0->digits[i] = cur % 10;
        carry = cur / 10;
    }
    in0->len = i;
}

void modpow_bigint(bigint *b, uint32_t e, bigint *m)
{
    (void)b;
    (void)e;
    (void)m;
    cout << "Not implemented " << endl;
}