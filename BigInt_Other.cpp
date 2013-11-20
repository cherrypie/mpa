#include "BigInt.h"

using std::cout;
using std::endl;

BigInt& BigInt::operator<<=(unsigned int a)
{
    if(a == 0)
    {
        return *this;
    }
    else if(a % (BITSINWORD) == 0)
    {
        a /= BITSINWORD;
        arr.resize(arr.size() + a, 0);
        for(size_t i = arr.size() - 1; i >= a; --i)
            arr[i] = arr[i - a];
        for(size_t i = 0; i < a; ++i)
            arr[i] = 0;
    }
    else if(a < BITSINWORD)
    {
        arr.push_back(arr[arr.size() - 1] >> (BITSINWORD  - a));
        for(int i = arr.size() - 2; i > 0; --i)
            arr[i] = (arr[i] << a) | (arr[i - 1] >> (BITSINWORD - a));
        arr[0] <<= a;
        while(arr.size() > 1 && arr[arr.size() - 1] == 0)arr.pop_back();
    }
    else
    {
        return (*this <<= a % (BITSINWORD)) <<= (a - a % (BITSINWORD));
    }

    return *this;
}

BigInt& BigInt::operator>>=(unsigned int a)
{
    if(a >= this->arr.size() * BITSINWORD)
    {
        this->arr.clear();
        this->arr.push_back(0);
    }
    else if(a % (BITSINWORD) == 0)
    {
        for(size_t i = 0; i < arr.size() - a / (BITSINWORD); ++i)
            arr[i] = arr[i + a / (BITSINWORD)];
        arr.resize(arr.size() - a / (BITSINWORD));
    }
    else if(a < BITSINWORD)
    {
        for(size_t i = 0; i < this->arr.size() - 1; ++i)
            this->arr[i] = (this->arr[i] >> a) | (this->arr[i + 1] << (BITSINWORD -  a)) ;
        this->arr[this->arr.size() - 1] >>= a;
        if(this->arr[this->arr.size() - 1] == 0)
            this->arr.pop_back();
    }
    else
    {
        return (*this >>= a % (BITSINWORD)) >>= a - a % (BITSINWORD);
    }

    return *this;
}

std::pair<BigInt, BigInt> BigInt::extended_gcd(BigInt a, BigInt b)
{
    BigInt x(0), lastx(1), y(1), lasty(0), q, temp, temptemp;
    std::pair<BigInt, BigInt> qr;
    while(! (b.arr[b.arr.size() - 1] == 0) )
    {
        qr = BigInt::div(a, b);
        q = qr.first;

        a = b;
        b = qr.second;

        temp = x;
        temptemp = q * x;
        x = lastx - temptemp;
        lastx = temp;

        temp = y;
        temptemp = q * y;
        y = lasty - temptemp;
        lasty = temp;
    }
    return std::pair<BigInt, BigInt>(lastx, lasty);
}

BigInt BigInt::getModuloPowerTwo(unsigned int k)
{
    if(k >= BITSINWORD * (arr.size()))
        return BigInt(*this);

    BigInt a;
    a.arr.clear();

    unsigned int i = 0;

    while(k >= BITSINWORD)
    {
        a.arr.push_back(arr[i]);
        ++i;
        k -= BITSINWORD;
    }

    if(k > 0)
        a.arr.push_back( (arr[i] << (BITSINWORD - k) ) >> (BITSINWORD - k) );

    return a;
}

unsigned int BigInt::getSize()
{
    return arr.size();
}
