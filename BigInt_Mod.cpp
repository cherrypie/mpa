#include "BigInt.h"

using std::cout;
using std::endl;

unsigned long long ext_gcd(unsigned long long a, unsigned long long b, long long& x, long long& y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    unsigned long long d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

unsigned long long inverse(unsigned long long a, unsigned long long n) {
    long long x, y;
    unsigned long long d = ext_gcd(a, n, x, y);
    if (d == 1) {
        while(x < 0) {
            x = x + n;
        }
        x = x % n;
        if (x * a % n != 1) {
            printf("bug");
        }
        return x;
    }
    return -1;
}

BigInt BigInt::Barrett(BigInt x, BigInt& n, BigInt& mu)
{
    BigInt q(x);
    unsigned int k = n.getSize();

    //Obtaining q with a cap
    q >>= (BITSINWORD * (k - 1));
    q = q * mu;
    q >>= (BITSINWORD * (k + 1));
    q = q * n;

    //The same as getModuloPowerTwo(BITSINWORD * (k + 1)), but much faster
    x.arr.resize(k + 1);
    q.arr.resize(k + 1);

    x = x - q;

    while(n < x || n == x)
        x = x - n;

    return x;
}

BigInt BigInt::Barrett(BigInt x, BigInt& n)
{
    BigInt mu = (BigInt(1) <<= (2 * n.getSize() * BITSINWORD)) / n;
    return Barrett(x, n, mu);
}


BigInt BigInt::MonRed(BigInt x, BigInt& n, unsigned int c0)
{
    if(x.arr.size() < n.arr.size())
        x.arr.resize(n.arr.size(), 0);

    BigInt a;

    for(size_t i = 0; i < n.arr.size(); ++i)
    {
        a = n * (c0 * x.arr[0]);
        x = x + a;
        x >>= BITSINWORD;
    }

    if(n < x || n == x)
        x = x - n;

    while(x.arr.size() > 1 && x.arr[x.arr.size() - 1] == 0) x.arr.pop_back();

    return x;
}

BigInt BigInt::MonPro(BigInt& x, BigInt& y, BigInt& n, unsigned int c)
{
    //Much slower than MonRed(x * y, n, c)
    if(x.arr.size() < n.arr.size()) x.arr.resize(n.arr.size(), 0);

    unsigned int t;

    BigInt A, temp;
    A.arr.resize(n.arr.size(), 0);

    for(size_t i = 0; i < n.arr.size(); ++i)
    {
        t = c * (x.arr[i] * y.arr[0] + A.arr[0]);
        temp = n * t;
        A = A + temp;
        temp = y * x.arr[i];
        A = A + temp;
        A >>= BITSINWORD;
    }

    if(n < A || n == A)
        A = A - n;

    while(x.arr.size() > 1 && x.arr[x.arr.size() - 1] == 0) x.arr.pop_back();
    while(y.arr.size() > 1 && y.arr[y.arr.size() - 1] == 0) y.arr.pop_back();

    return A;
}

BigInt BigInt::MonPow(BigInt& x, BigInt& d, BigInt n)
{
    if(n.arr[n.arr.size() - 1] == 0){
        std::cerr << "Dividing by zero!\n";
        return BigInt(0);
    }
    if(x.arr[x.arr.size() - 1] == 0 || (x.getSize() == 1 && x.arr[0] == 1) || (d.arr.size() == 1 && d.getSize() == 1)) return x;
    if(d.arr[d.arr.size() - 1] == 0) return BigInt(1);

    if(n.arr[0] & 1) return MonPowOdd(x, d, n);

    unsigned int k = 0;
    while(n.arr[k / BITSINWORD] == 0) k += BITSINWORD;
    while( !( (n.arr[k / BITSINWORD] >> k % 32 ) & 1) ) ++k;

    BigInt odd = MonPowOdd(x, d, n >>= k);
    BigInt even = ExpModuloPowerTwo(x, d, k);

    BigInt PowerOfTwo = (BigInt(1) <<= k);

    std::pair<BigInt, BigInt> uv = BigInt::extended_gcd(n, PowerOfTwo);

    //BigInt result = uv.first * even * n + uv.second * odd * PowerOfTwo;
    BigInt result, temp;

    temp = odd * PowerOfTwo;
    temp = temp * uv.second;
    result = temp;

    temp = even * n;
    temp = temp * uv.first;
    result = result + temp;

    n <<= k;

    result = result % n;

    if(!result.nonNegative) result = result + n;

    return result;

}

BigInt BigInt::MonPowOdd(BigInt x, BigInt& d, BigInt& n)
{
    if(x.arr.size() < n.arr.size())
        x.arr.resize(n.arr.size(), 0);
    if(d.arr.size() < n.arr.size())
        d.arr.resize(n.arr.size(), 0);

    unsigned int c = (unsigned int) (BigInt::Base - inverse(n.arr[0], BigInt::Base));
    BigInt mu = (BigInt(1) <<= (2 * n.arr.size() * BITSINWORD)) / n;
    BigInt m_x = Barrett(x <<= (BITSINWORD * n.arr.size()), n, mu);
    BigInt m_y = Barrett(BigInt(1) <<= (BITSINWORD * n.arr.size()), n, mu);

    int high_bit = BITSINWORD - 1;
    while( (d.arr[d.arr.size() - 1] >> high_bit) == 0 ) --high_bit;

    for(int i = high_bit; i >= 0; --i)
    {
        m_y = MonRed(m_y.Square(), n, c);
        if( (( d.arr[d.arr.size() - 1] >> i ) & 1) == 1)
            m_y = MonRed(m_y * m_x, n, c);
    }

    for(int i = d.arr.size() - 2; i >= 0; --i)
    {
        for(int j = BITSINWORD - 1; j >= 0; --j)
        {
            m_y = MonRed(m_y.Square(), n, c);
            if( ( (d.arr[i] >> j) & 1 ) == 1)            
                m_y = MonRed(m_y * m_x, n, c);
        }
    }

    m_y = MonRed(m_y, n, c);

    while(x.arr.size() > 1 && x.arr[x.arr.size() - 1] == 0) x.arr.pop_back();
    while(d.arr.size() > 1 && d.arr[d.arr.size() - 1] == 0) d.arr.pop_back();

    return m_y;
}

BigInt BigInt::ExpModuloPowerTwo(BigInt& x, BigInt& d, unsigned int k)
{
    BigInt y(1);

    int high_bit = BITSINWORD - 1;
    while( (d.arr[d.arr.size() - 1] >> high_bit) == 0 ) --high_bit;

    for(int i = high_bit; i >= 0; --i)
    {
        y = y.Square().getModuloPowerTwo(k);
        if( (( d.arr[d.arr.size() - 1] >> i ) & 1) == 1)
            y = (y * x).getModuloPowerTwo(k);
    }

    for(int i = d.arr.size() - 2; i >= 0; --i)
    {
        for(int j = BITSINWORD - 1; j >= 0; --j)
        {
            y = y.Square().getModuloPowerTwo(k);
            if( ( (d.arr[i] >> j) & 1 ) == 1)
                y = (y * x).getModuloPowerTwo(k);
        }
    }

    return y;
}


BigInt BigInt::Pow(BigInt& x, BigInt& d, BigInt& n)
{
    BigInt y(1);
    BigInt mu = (BigInt(1) <<= (2 * n.arr.size() * BITSINWORD)) / n;
    BigInt nSquared = n.Square();

    int high_bit = BITSINWORD - 1;
    while( (d.arr[d.arr.size() - 1] >> high_bit) == 0 ) --high_bit;

    for(int i = high_bit; i >= 0; --i)
    {
        y = y.Square();
        if(nSquared < y)
            y = Barrett(y, n, mu);
        else
            y = y % n;

        if( (( d.arr[d.arr.size() - 1] >> i ) & 1) == 1)
        {
            y = y * x;
            if(nSquared < y)
                y = Barrett(y, n, mu);
            else
                y = y % n;
        }
    }
    for(int i = d.arr.size() - 2; i >= 0; --i)
    {
        for(int j = BITSINWORD - 1; j >= 0; --j)
        {
            y = y.Square();
            if(nSquared < y)
                y = Barrett(y, n, mu);
            else
                y = y % n;

            if( ( (d.arr[i] >> j) & 1 ) == 1)
            {
                y = y * x;
                if(nSquared < y)
                    y = Barrett(y, n, mu);
                else
                    y = y % n;
            }
        }
    }

    return y;
}
