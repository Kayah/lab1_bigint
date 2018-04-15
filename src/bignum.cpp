#include "biginteger.hpp"

void bignum::output()
{
    for (int i = amount-1 ; i >= 0; i--)
        std::cout << digits[i];
    std::cout << std::endl;
}

void bignum::LevelUp()
{
    for (int i = amount; i >= 1; i--)
        digits[i] = digits[i-1];
    if (digits[amount])
        amount++;
} 

uint64_t bignum::toint()
{
    uint64_t result = 0;
    uint64_t tmp = 1;
    for (int i = 0; i < 4; i++)
    {
        result = result + digits[i] * tmp;
        tmp *= 10;
    }
    return result;
}

bignum operator + (const bignum &a, const bignum &b)
{
    bignum res;
    res.amount = std::max(a.amount,b.amount);
    int r = 0;
    for (int i=0;i<res.amount | r;i++)
    {
        res.digits[i] = a.digits[i] + b.digits[i] + r;
        if (res.digits[i]>=osn)
        {
            res.digits[i]-=osn;
            r = 1;
        }
        else
            r = 0;
    }
    if (res.digits[res.amount])
        res.amount++; 
    
    return res;
}

bignum operator * (const bignum &a, const bignum &b)
{
    bignum res;
    for (int i=0;i<a.amount;i++)
    {
        int r = 0;
        for (int j=0; j < b.amount|r; j++)
        {
            res.digits[i+j] += a.digits[i] * b.digits[j] + r;
            r = res.digits[i+j] / osn;
            res.digits[i+j] -= r*osn;
        }
    }
    int pos = a.amount + b.amount;
    while (pos>0 && !res.digits[pos])
          pos--;
    res.amount = pos + 1;
    if (a.isMinus && b.isMinus)
        res.isMinus = false;
    else if ((a.isMinus && !b.isMinus) || (!a.isMinus && b.isMinus))
        res.isMinus = true;
    
    return res;
}

bignum operator * (const bignum &a, const int &n)
{
    bignum res;
    res.amount = a.amount;
    int r = 0;
    for (int i=0;i<res.amount | r;i++)
    {
        res.digits[i] = a.digits[i] * n + r;
        r = res.digits[i]/osn;
        res.digits[i] -= r*osn;
    }
    if (res.digits[res.amount])
        res.amount++;
    return res;
}
 
bignum operator - (const bignum &a, const bignum &b)
{
  bignum res = a;
  int r = 0;
  for (int i = 0; i < res.amount; i++)
  {
    res.digits[i] -= b.digits[i] + r;
    if (res.digits[i] < 0)
    {
      res.digits[i] += osn;
      res.digits[i+1]--;
    }   
  }
  int pos = res.amount;
  while (pos && !res.digits[pos])
    pos--;
  res.amount = pos + 1;
  return res;
}

bignum operator -(const bignum &a, const int b)
{
    bignum res = a;
    int pos = 0;
    res.digits[0] -= b;
    
    while(res.digits[pos] < 0)
    {
        res.digits[pos+1] --;
        res.digits[pos++] +=osn;
    }

    if (res.amount && !res.digits[res.amount-1])
        res.amount--;
    return res;
}

bool operator == (const bignum &a, const int &n)
{
    if (a.digits[0] != n)
          return false;
    return true;
}

bool operator == (const bignum &a, const bignum &b)
{
    if (a.amount != b.amount)
          return false;
    for (int i=0; i < a.amount; i++)
    {
        if (a.digits[i] != b.digits[i])
            return false;
    }
    return true;
}

// bignum operator &(const bignum &a, const int b)
// {
//     bignum result;
//     std::cout << "NOT IMPLEMENTED : " << __func__ << std::endl;
//     // for (int i = a.amount - 1; i >=0; i--)
//     // {
//     //     result.digits[i] = a.digits[i] & b;
//     // }
//     return result;
// }

bool operator > (const bignum &a, const bignum &b)
{
    if (a.amount != b.amount)
        return a.amount > b.amount;
    for (int i = a.amount-1; i >= 0; i--)
    {
        if (a.digits[i] != b.digits[i])
            return a.digits[i] > b.digits[i];
    }
    return false;
}

bool operator < (const bignum &a, const bignum &b)
{
    if (a.amount != b.amount)
        return a.amount < b.amount;
    for (int i = a.amount-1; i >= 0; i--)
    {
        if (a.digits[i] != b.digits[i])
            return a.digits[i] < b.digits[i];
    }
    return false;
}

bignum add(const bignum &a, const bignum &b)
{
    bignum c;
    
    if (a.isMinus && !b.isMinus)
    {
        c = minus(b,a);
    }
    else if (!a.isMinus && b.isMinus)
    {
        c = minus(a,b);
    }
    else
    {
        c = a + b;
    }
    return c;
}

bignum minus(const bignum &a, const bignum &b)
{
    bignum c;
    if (a < b)
    {
        c = b - a;
        c.isMinus = true;
    }
    else
        c = a - b; 
    if (a.isMinus && b.isMinus)
    {
        c = a + b;
        c.isMinus = true;
    }
    
    return c;
}

bignum operator / (const bignum &a, const bignum &b)
{
    bignum res;
    bignum curValue;
    for (int i = a.amount-1; i >= 0; i--)
    {
        curValue.LevelUp();
        curValue.digits[0] = a.digits[i];
        int x = 0;
        int l = 0, r = osn;
        while(l <= r)
        {
            int m = (l + r) >> 1;
            bignum cur = b * m;
            if (!(cur > curValue))
            {
                x = m;
                l = m+1;
            }
            else
                r = m-1;
        }
        res.digits[i] = x;
        curValue = curValue - b * x;
    } 
    int pos = a.amount;
    while(pos >= 0 && !res.digits[pos])
        pos--;
    res.amount = pos + 1;
    return res;
}

bignum operator / (const bignum &a, const int &n)
{
    bignum res;
    res.amount = a.amount;
    int ost = 0;
    for (int i = res.amount-1; i >= 0; i--)
    {
        int cur = ost * osn + a.digits[i];
        res.digits[i] = cur / n;
        ost = cur % n;
    }
    if (!res.digits[res.amount-1] && res.amount != 1)
        res.amount--;
    
    res.isMinus = a.isMinus;
    return res;
} 

bignum operator % (const bignum &a, const bignum &b)
{
    bignum res;
    bignum curValue;
    for (int i = a.amount-1; i>=0; i--)
    {
        curValue.LevelUp();
        curValue.digits[0] = a.digits[i];
        int x = 0;
        int l = 0, r = osn;
        while(l <= r)
        {
            int m = (l + r) >> 1;
            bignum cur = b * m;
            if (!(cur > curValue))
            {
                x = m;
                l = m + 1;
            }   
            else
                r = m - 1;
        }
        res.digits[i] = x;
        curValue = curValue - b * x;
    }
    return curValue;
}

bignum bignum_modpow(bignum &b, bignum &e, bignum &m)
{
    bignum result(1);
    // while(e > 0)
    // {
        // e.output();
        // if ((e.digits[0] & 1) == 1)
        // {
            // std::cout << " mod = 1  "; e.output(); std::cout << std::endl;
            // result = (result * b) % m;
        // }
        // b = (b * b) % m;
        // e = e / 2;
    // }
    std::cout << "NOT IMPLEMENTED : " << __func__ << std::endl;
    return result;
}