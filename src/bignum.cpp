#include "biginteger.hpp"

void bignum::input()
{
    memset(digits,0,sizeof(digits));
    std::string str;
    std::cin >> str;
    int pos = 0;
    for (int i=str.size()-1;i>=0;i--)
      digits[pos++] = str[i] - '0';
    amount = str.size();
} 

void bignum::output()
{
    for (int i=amount-1;i>=0;i--)
        std::cout<<digits[i];
    std::cout<<std::endl;
}

void bignum::LevelUp()
{
    for (int i = amount;i>=1;i--)
        digits[i] = digits[i-1];
    if (digits[amount])
        amount++;
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
  for (int i = 0;i<res.amount;i++)
  {
    res.digits[i] -= b.digits[i] + r;
    if (res.digits[i]<0)
    {
      res.digits[i]+=osn;
      res.digits[i+1]--;
    }   
  }
  int pos = res.amount;
  while (pos && !res.digits[pos])
    pos--;
  res.amount = pos+1;
  return res;
}

bool operator == (const bignum &a, const bignum &b)
{
    if (a.amount!=b.amount)
          return false;
    for (int i=0;i<a.amount;i++)
    {
        if (a.digits[i]!=b.digits[i])
            return false;
    }
    return true;
}

bool operator > (const bignum &a, const bignum &b)
{
    if (a.amount!=b.amount)
        return a.amount>b.amount;
    for (int i=a.amount-1;i>=0;i--)
    {
        if (a.digits[i]!=b.digits[i])
            return a.digits[i]>b.digits[i];
    }
    return false;
}

bool operator < (const bignum &a, const bignum &b)
{
    if (a.amount!=b.amount)
        return a.amount<b.amount;
    for (int i=a.amount-1;i>=0;i--)
    {
        if (a.digits[i]!=b.digits[i])
            return a.digits[i]<b.digits[i];
    }
    return false;
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
    if (c.isMinus) 
        std::cout<<"-";
    c.output(); 
}

bignum operator / (const bignum &a, const bignum &b)
{
    bignum res;
    bignum curValue;
    for (int i = a.amount-1; i>=0; i--)
    {
        curValue.LevelUp();
        curValue.digits[0] = a.digits[i];
        int x = 0;
        int l = 0, r = osn;
        while (l <= r)
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
    while (pos>=0 && !res.digits[pos])
        pos--;
    res.amount = pos+1;
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
        while (l <= r)
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
    return curValue;
}

