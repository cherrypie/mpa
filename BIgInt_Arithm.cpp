#include "BigInt.h"

BigInt& BigInt::uAdd(BigInt& a)
{
    int carry = 0;
    unsigned long long temp = 0;
    size_t i = 0;
    for(; i < a.arr.size(); ++i)
    {
        temp = (long long) arr[i] + a.arr[i] + carry;
        arr[i] = (unsigned int) temp;
        carry = temp >> (BITSINWORD);
    }
    for(; carry != 0 && i < arr.size(); ++i)
    {
        arr[i] += carry;
        carry = arr[i] == 0? 1 : 0;
    }
    if(carry != 0)
        arr.push_back(1);

    return *this;
}

BigInt operator+(BigInt& a, unsigned int b)
{
    BigInt c = a;
    unsigned long long temp = c.arr[0] + b;
    c.arr[0] = (unsigned int) temp;
    if(temp >> BITSINWORD)
    {
        int carry = 1;
        for(size_t i = 1; carry != 0 && i < c.arr.size(); ++i)
        {
            c.arr[i] += carry;
            carry = c.arr[i] == 0? 1 : 0;
        }
        if(carry == 1)
            c.arr.push_back(1);
    }
    return c;
}

BigInt& BigInt::uSub(BigInt& a)
{
    int carry = 0;
    size_t i = 0;
    for(; i < a.arr.size(); ++i)
    {
        if( arr[i] - a.arr[i] + carry > arr[i])
        {
            arr[i] = arr[i] - a.arr[i] + carry;
            carry = -1;
        }
        else
        {
            arr[i] = arr[i] - a.arr[i] + carry;
            carry = 0;
        }
    }
    for(; ( carry != 0 ) && ( i < arr.size() ); ++i)
    {
        if(arr[i] > 0)
        {
            carry = 0;
            --arr[i];
        }
    }

    while( ( arr.size() > 1 ) && ( arr[arr.size() - 1] == 0 ) ) arr.pop_back();

    return *this;
}

BigInt operator+(BigInt& a, BigInt& b)
{
    if(a < b)
        return b + a;

    if(a.nonNegative ^ b.nonNegative)
        return BigInt(a).uSub(b);
    else
        return BigInt(a).uAdd(b);
}

BigInt operator-(BigInt& a, BigInt& b)
{
    if(a == b) return BigInt(0);

    BigInt c;

    b.nonNegative = 1 - b.nonNegative;

    if(a.nonNegative ^ b.nonNegative)
    {
        if(a < b)
            c = BigInt(b).uSub(a);
        else
            c = BigInt(a).uSub(b);
    }
    else
    {
        b.nonNegative = 1 - b.nonNegative;
        if(a < b)
            c = BigInt(b).uAdd(a);
        else
            c = BigInt(a).uAdd(b);
    }

    b.nonNegative = 1 - b.nonNegative;

    return c;
}

BigInt BigInt::Square()
{
    BigInt b;
    b.arr.resize(arr.size() * 2, 0);
    b.nonNegative = 1;

    unsigned long long temp;
    unsigned int carry;

    for(size_t i = 0; i < arr.size(); ++i)
    {
        carry = 0;
        for(size_t j = i + 1; j < arr.size(); ++j)
        {
            temp = (unsigned long long) arr[i] * arr[j] + b.arr[i + j] + carry;
            b.arr[i + j] = (unsigned int) temp;
            carry = temp >> BITSINWORD;
        }
        b.arr[i + arr.size()] = carry;
    }

    b <<= 1;

    if(b.arr.size() < arr.size() * 2)
        b.arr.resize(arr.size() * 2, 0);

    carry = 0;

    for(size_t i = 0, ind = 0; i < arr.size(); ++i)
    {
        temp = (unsigned long long) arr[i] * arr[i] + b.arr[ind] + carry;
        b.arr[ind++] = (unsigned int) temp;
        carry = temp >> BITSINWORD;
        temp = (unsigned long long) b.arr[ind] + carry;
        b.arr[ind++] = (unsigned int) temp;
        carry = temp >> BITSINWORD;
    }

    while(b.arr.size() > 1 && b.arr[b.arr.size() - 1] == 0) b.arr.pop_back();
    return b;
}


BigInt operator*(BigInt& a, unsigned int b)
{
    BigInt c;
    c.arr.resize(a.arr.size());
    c.nonNegative = a.nonNegative;

    unsigned long long product = (unsigned long long) a.arr[0] * b;
    unsigned int carry = (product >> BITSINWORD);
    c.arr[0] = (unsigned int) product;

    for(size_t i = 1; ( carry != 0 ) && ( i < c.arr.size() ); ++i)
    {
        product = (unsigned long long)a.arr[i] * b + carry;
        carry = (product >> BITSINWORD);
        c.arr[i] = (unsigned int) product;
    }
    if(carry != 0)
        c.arr.push_back(carry);
    return c;
}

BigInt operator*(BigInt& a, BigInt& b)
{
    BigInt c(0);
    if(a.nonNegative ^ b.nonNegative) c.nonNegative = 0;
    c.arr.resize(a.arr.size() + b.arr.size(), 0);

    size_t i, j;
    unsigned int carry;
    unsigned long long product;
    for(i = 0; i < a.arr.size(); ++i)
    {
        carry = 0;
        for(j = 0; j < b.arr.size(); ++j)
        {
            product = (long long) a.arr[i] * b.arr[j] + c.arr[i + j]  + carry;
            c.arr[i + j] = (unsigned int) product;
            carry = (unsigned int) (product >> (BITSINWORD));
        }
        c.arr[i + j] = carry;
    }

    i = c.arr.size() - 1;
    while(i > 0 && c.arr[i] == 0) --i;
    c.arr.resize(i + 1);

    return c;
}


BigInt operator/(BigInt& a, BigInt& b)
{
    return BigInt::div(a, b).first;
}

BigInt operator/(BigInt& a, unsigned int b)
{
    return BigInt::divByte(a,b).first;
}

BigInt operator%(BigInt& a, BigInt& b)
{
    return BigInt::div(a, b).second;
}

BigInt operator%(BigInt& a, unsigned int b)
{
    return BigInt::divByte(a, b).second;
}

std::pair<BigInt, unsigned int> BigInt::divByte(BigInt& a, unsigned int& b)
{
    if(b == 0)
    {
      std::cout << "DIVIDING BY ZERO!\n";
      return std::make_pair(BigInt(0), 0);
    }

    unsigned int r = 0;
    BigInt q;
    q.arr.resize(a.arr.size());
    for(int i = a.arr.size() - 1; i >= 0; --i)
    {
        q.arr[i] = ( (((unsigned long long) r) << BITSINWORD) + a.arr[i]) / b;
        r = ((((unsigned long long) r) << BITSINWORD) + a.arr[i]) % b;
    }
    return std::make_pair(q, r);
}


std::pair<BigInt, BigInt> BigInt::div(BigInt a, BigInt& b)
{
    if(b.arr.size() == 1)
        return divByte(a, (b.arr[0]));

    BigInt q;

    //Normalise
    unsigned int d;
    for(d = 0; (b.arr[b.arr.size() - 1] << d) < a.c1; ++d);
    b <<= d;
    a.arr.push_back(0);
    a <<= d;

    unsigned int n = b.arr.size();
    unsigned int m = a.arr.size() - n - 1;
    unsigned long long qq, rem, temp;
    int carrya;
    unsigned int carryb;
    long long temptemp;
    for(int j = m; j >= 0; --j)
    {
        qq = ((unsigned long long)a.arr[j + n] * BigInt::Base + a.arr[j + n - 1]) / b.arr[b.arr.size() - 1];
        rem = ((unsigned long long)a.arr[j + n] * BigInt::Base + a.arr[j + n - 1]) - b.arr[b.arr.size() - 1] * qq;

        if(qq == BigInt::Base || qq * b.arr[b.arr.size() - 2] > rem * BigInt::Base + a.arr[j + n - 2])
        {
            --qq;
            rem += b.arr[n - 1];
            if(rem < BigInt::Base && qq * b.arr[n - 2] > rem * BigInt::Base + a.arr[j + n - 2])
                --qq;
        }

        carrya = carryb = 0;
        for(size_t i = 0; i < n; ++i)
        {
            temp = qq * b.arr[i] + carryb;
            carryb = temp >> BITSINWORD;
            temptemp = (long long)a.arr[j + i] + carrya - (unsigned int)temp;
            if(temptemp >= 0)
            {
                a.arr[j + i] = (unsigned int)temptemp;
                carrya = 0;
            }
            else
            {
                a.arr[j + i] = (unsigned int)(temptemp + BigInt::Base);
                carrya = -1;
            }

        }
        temptemp = (long long)a.arr[j + n] - carryb + carrya;

        if(temptemp == 0)
        {
            a.arr[j + n] = 0;
        }
        else if(temptemp == -1)
        {
            carrya = 0;
            for(size_t i = 0; i < n; ++i)
            {
                rem = a.arr[j + i] + b.arr[i] + carrya;
                carrya = rem >> (BITSINWORD);
            }
            --qq;
        }

        q.arr.insert(q.arr.begin(), (unsigned int) qq);
    }

    b >>= d;
    while(q.arr.size() > 1 && q.arr[q.arr.size() - 1] == 0) q.arr.pop_back();
    while(a.arr.size() > 1 && a.arr[a.arr.size() - 1] == 0) a.arr.pop_back();

    return std::make_pair(q, a >>= d);
}
