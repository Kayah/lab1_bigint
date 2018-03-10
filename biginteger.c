/* 
** file: biginteger.h
*/
#include "biginteger.h"

/**
 * zero_justify
 * input: input bigint
 */
static void
zero_justify(bigint *n)
{
	while ((n->lastdigit > 0) && (n->digits[ n->lastdigit ] == 0))
		n->lastdigit --;

    if ((n->lastdigit == 0) && (n->digits[0] == 0))
		n->signbit = PLUS;
}

/**
 * shift function, 
 * n: input bigint
 * d: 
 */
static void
shift(bigint *in, int d)
{
    if (!in)
        return;

    if ((in->lastdigit == 0) && (in->digits[0] == 0))
        return;

    for (int i = in->lastdigit; i >= 0; i--)
        in->digits[i+d] = in->digits[i];
    
    for (int i = 0; i < d; i++)
        in->digits[i] = 0;

    in->lastdigit = in->lastdigit + d;
}

/**
 * compare_bigint
 * input: *a bigint, *b bigint
 */
static int
compare_bigint(bigint *a, bigint *b)
{
	int i;		

	if ((a->signbit == MINUS) && (b->signbit == PLUS)) return(PLUS);
	if ((a->signbit == PLUS) && (b->signbit == MINUS)) return(MINUS);

	if (b->lastdigit > a->lastdigit) return (PLUS * a->signbit);
	if (a->lastdigit > b->lastdigit) return (MINUS * a->signbit);

	for (i = a->lastdigit; i>=0; i--) {
		if (a->digits[i] > b->digits[i]) return(MINUS * a->signbit);
		if (b->digits[i] > a->digits[i]) return(PLUS * a->signbit);
	}

	return 0;
}

void
print_bigint(const bigint *input)
{
    for(int i = input->lastdigit; i >= 0; i--)
    {
        printf("%d", input->digits[i]);
    }
    printf("\n");
}

void
init_bigint(const char *input, uint32_t input_length, int signbit, bigint *out)
{
    uint32_t i;
    uint32_t j;
    
    if (!input || (input_length == 0))
    {
        printf("Error, input == NULL, %s %s %d", __FILE__, __func__, __LINE__);
    }

    if (input_length > MAXINPUT)
    {
        printf("Error, input_length > MAXINPUT, %s %s %d", __FILE__, __func__, __LINE__);
    }

    if (signbit > 0) 
        out->signbit = PLUS;
    else 
        out->signbit = MINUS;
    
    for (i = 0, j = input_length-1; i < input_length; i++, j--)
    {
        out->digits[i] = input[j]-'0';
    }
    out->lastdigit = input_length;
}

void
subtract_bigint(bigint *a, bigint *b, bigint *c)
{
	int borrow;			
	int v;				
	int i;				

	memset(c->digits, 0, MAXINPUT);

	if ((a->signbit == MINUS) || (b->signbit == MINUS)) {
                b->signbit = -1 * b->signbit;
                add_bigint(a,b,c);
                b->signbit = -1 * b->signbit;
		return;
        }

	if (compare_bigint(a,b) == PLUS) {
		subtract_bigint(b,a,c);
		c->signbit = MINUS;
		return;
	}

        c->lastdigit = max(a->lastdigit,b->lastdigit);
        borrow = 0;

        for (i=0; i<=(c->lastdigit); i++) {
		v = (a->digits[i] - borrow - b->digits[i]);
		if (a->digits[i] > 0)
			borrow = 0;
		if (v < 0) {
			v = v + 10;
			borrow = 1;
		}

                c->digits[i] = (char) v % 10;
        }

	zero_justify(c);
}

void 
add_bigint(bigint *in0, bigint *in1, bigint *out)
{
    int i;
    int carry;
    int carry_last_digit;
    int *digits_ptr;

    if (!in0 || !in1 || !out)
    {
        printf("Error, in0 == NULL || in1 == NULL || out == NULL, %s %s %d", \
                 __FILE__, __func__, __LINE__);
        return;
    }
    memset(out->digits, 0, MAXINPUT);

    if (in0->signbit == in1->signbit) out->signbit = in0->signbit;
	else {
		if (in0->signbit == MINUS) {
			in0->signbit = PLUS;
			subtract_bigint(in1,in0,out);
			in0->signbit = MINUS;
		} else {
                        in1->signbit = PLUS;
                        subtract_bigint(in0,in1,out);
                        in1->signbit = MINUS;
		}
		return;
	}

    if (in0->lastdigit > in1->lastdigit)
    {
        carry_last_digit = in1->lastdigit;
        digits_ptr = in0->digits;
    }
    else
    {
        carry_last_digit = in0->lastdigit;
        digits_ptr = in1->digits;
    }
    
    out->lastdigit = max(in0->lastdigit, in1->lastdigit) + 1;    

    for (i = 0, carry = 0; i <= out->lastdigit; i++)
    {
        out->digits[i] = (carry + in0->digits[i] + in1->digits[i]) % 10;
        carry = (carry + in0->digits[i] + in1->digits[i]) / 10;
    }
    zero_justify(out);
}

void
mult_bigint(bigint *a, bigint *b, bigint *c)
{
    bigint row;			
	bigint tmp;			
	
    if (!a || !b || !c)
        return;

    row = *a;

	for (int i=0; i<=b->lastdigit; i++) {
		for (int j=1; j<=b->digits[i]; j++) {
            add_bigint(c,&row,&tmp);
			*c = tmp;
		}
		shift(&row,1);
	}
    zero_justify(c);
}
