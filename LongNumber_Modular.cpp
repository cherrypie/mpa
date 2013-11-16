#include "LongNumber.h"

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

LongNumber LongNumber::Barrett(LongNumber x, LongNumber& n, LongNumber& mu)
{
    if(x < n) return x;

    unsigned int k = n.arr.size();

    if(x.arr.size() > 2 * k)
        return x % n;
    else
        x.arr.resize(2 * k, 0);

    LongNumber q = x;

    q >>= ((k - 1) * BITSINWORD);				//q1
    q = q * mu;									//q2
    q >>= ((k + 1) * BITSINWORD);				//q3

    if(x.arr.size() > k + 1)
        x.arr.resize(k + 1);					//x mod b^(k+1)

    q = q * n;									//q3 * n

    if(q.arr.size() > k + 1)
        q.arr.resize(k + 1);

    q = x - q;
    while(q == n || n < q){q = q - n;}
    //Some problems with almost ininite loop

    return q;
}

LongNumber LongNumber::MonRed(LongNumber x, LongNumber& n)
{
    if(x.arr.size() < n.arr.size())
        x.arr.resize(n.arr.size(), 0);

    unsigned int tempc = (unsigned int) (LongNumber::Base - inverse(n.arr[0], LongNumber::Base));

    for(size_t i = 0; i < n.arr.size(); ++i)
        //x = ((x + n * (tempc * x.arr[0])) >>= BITSINWORD);

    if(n < x || n == x)
        x = x - n;

    while(x.arr.size() > 1 && x.arr[x.arr.size() - 1] == 0) x.arr.pop_back();

    return x;
}
LongNumber LongNumber::MonPro(LongNumber& x, LongNumber& y, LongNumber& n, unsigned int c)
{
    return LongNumber::MonRed(x * y, n);
    //yeah, all is right :/


    if(x.arr.size() < n.arr.size()) x.arr.resize(n.arr.size(), 0);

    if(c == 0)
        c = (unsigned int) (LongNumber::Base - inverse(n.arr[0], LongNumber::Base));

    unsigned int t;

    LongNumber A;
    A.arr.resize(n.arr.size(), 0);

    for(size_t i = 0; i < n.arr.size(); ++i)
    {
        t = c * (x.arr[i] * y.arr[0] + A.arr[0]);
        //A = (A + n * t + y * x.arr[i]);
        A >>= BITSINWORD;
    }

    if(n < A || n == A)
        A = A - n;

    while(x.arr.size() > 1 && x.arr[x.arr.size() - 1] == 0) x.arr.pop_back();
    while(y.arr.size() > 1 && y.arr[y.arr.size() - 1] == 0) y.arr.pop_back();

    return A;
}

LongNumber LongNumber::MonPow(LongNumber& x, LongNumber& d, LongNumber n)
{
    if( x.arr[x.arr.size() - 1] == 0 || (x.getSize() == 1 && x.arr[0] == 1) || (d.arr.size() == 1 && d.getSize() == 1)) return x;
    if(d.arr[d.arr.size() - 1] == 0) return LongNumber(1);

    if(n.arr[0] & 1) return MonOddPow(x, d, n);

    unsigned int k = 0;
    while(n.arr[k / BITSINWORD] == 0) k += BITSINWORD;
    while( !( (n.arr[k / BITSINWORD] >> k % 32 ) & 1) ) ++k;

    LongNumber even = n.getModuloPowerTwo(k), odd = MonOddPow(x, d, n >>= k);

    std::pair<LongNumber, LongNumber> uv = LongNumber::extended_gcd(n, k);

    //todo

    return x;
}

LongNumber LongNumber::MonOddPow(LongNumber& x, LongNumber& d, LongNumber& n)
{
    if(x.arr.size() < n.arr.size())
        x.arr.resize(n.arr.size(), 0);
    if(d.arr.size() < n.arr.size())
        d.arr.resize(n.arr.size(), 0);

    unsigned int c = (unsigned int) (LongNumber::Base - inverse(n.arr[0], LongNumber::Base));
    LongNumber mu = (LongNumber(1) <<= (2 * n.arr.size() * BITSINWORD)) / n;
    LongNumber m_x = Barrett(x <<= (BITSINWORD * n.arr.size()), n, mu);
    LongNumber m_y = Barrett(LongNumber(1) <<= (BITSINWORD * n.arr.size()), n, mu);

    int high_bit = BITSINWORD - 1;
    while( (d.arr[d.arr.size() - 1] >> high_bit) == 0 ) --high_bit;

    for(int i = high_bit; i >= 0; --i)
    {
        //m_y = MonRed(m_y.Square(), n);
        m_y = MonPro(m_y, m_y, n, c);
        if( (( d.arr[d.arr.size() - 1] >> i ) & 1) == 1)
        {
            //m_y = MonRed(m_y * m_x, n);
            m_y = MonPro(m_y, m_x, n, c);
        }
    }

    for(int i = d.arr.size() - 2; i >= 0; --i)
    {
        for(int j = BITSINWORD - 1; j >= 0; --j)
        {
            //m_y = MonRed(m_y.Square(), n);
            m_y = MonPro(m_y, m_y, n, c);
            if( ( (d.arr[i] >> j) & 1 ) == 1)
            {
                //m_y = MonRed(m_y * m_x, n);
                m_y = MonPro(m_y, m_x, n, c);
            }
        }
    }

    m_y = MonRed(m_y, n);

    while(x.arr.size() > 1 && x.arr[x.arr.size() - 1] == 0) x.arr.pop_back();
    while(d.arr.size() > 1 && d.arr[d.arr.size() - 1] == 0) d.arr.pop_back();

    return m_y;
}

LongNumber LongNumber::Pow(LongNumber& x, LongNumber& d, LongNumber& n)
{
    LongNumber y(1);
    LongNumber mu = (LongNumber(1) <<= (2 * n.arr.size() * BITSINWORD)) / n;

    int high_bit = BITSINWORD - 1;
    while( (d.arr[d.arr.size() - 1] >> high_bit) == 0 ) --high_bit;

    for(int i = high_bit; i >= 0; --i)
    {

        y = Barrett(y.Square(), n, mu);
        if( (( d.arr[d.arr.size() - 1] >> i ) & 1) == 1)
            y = Barrett(y * x, n, mu);
    }
    for(int i = d.arr.size() - 2; i >= 0; --i)
    {
        for(int j = BITSINWORD - 1; j >= 0; --j)
        {
            y = Barrett(y.Square(), n, mu);
            if( ( (d.arr[i] >> j) & 1 ) == 1)
                y = Barrett(y * x, n, mu);
        }
    }

    return y;
}
