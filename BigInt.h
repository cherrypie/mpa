#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <stdio.h>

#define BITSINWORD 32

class BigInt
{
public:
	std::vector <unsigned int> arr;
	bool nonNegative;

    BigInt& uAdd(BigInt&);
    BigInt& uSub(BigInt&);
    static std::pair<BigInt, unsigned int> divByte(BigInt&, unsigned int&);
    static std::pair<BigInt, BigInt> div(BigInt, BigInt&);
    static unsigned int const c1 = 0x7fffffff;
    static unsigned long long const Base = 1ULL << sizeof(int) * 8;

public:

    /*      Input/Output            */
    BigInt();
    BigInt(unsigned int);
    BigInt(std::string);
    BigInt(const BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);


    /*      Comparison operators    */
    friend bool operator<(BigInt&, BigInt&);
    friend bool operator==(BigInt&, BigInt&);


    /*      Arithmetic operations   */
    friend BigInt operator+(BigInt&, BigInt&);
    friend BigInt operator+(BigInt&, unsigned int);
    friend BigInt operator-(BigInt&, BigInt&);
    friend BigInt operator*(BigInt&, BigInt&);
    friend BigInt operator*(BigInt&, unsigned int);
    friend BigInt operator/(BigInt&, BigInt&);
    friend BigInt operator/(BigInt&, unsigned int);
    friend BigInt operator%(BigInt&, BigInt&);
    friend BigInt operator%(BigInt&, unsigned int);
    BigInt Square();


    /*      Modular operations      */
private:
    static BigInt Barrett(BigInt, BigInt&, BigInt&);
    static BigInt MonRed(BigInt, BigInt&, unsigned int);
    static BigInt MonPro(BigInt&, BigInt&, BigInt&, unsigned int);
    static BigInt MonPowOdd(BigInt, BigInt&, BigInt&);
    static BigInt ExpModuloPowerTwo(BigInt&, BigInt&, unsigned int);
public:
    static BigInt Barrett(BigInt, BigInt&);
    static BigInt MonPow(BigInt&, BigInt&, BigInt);
    static BigInt Pow(BigInt&, BigInt&, BigInt&);

    /*      Other stuff             */
    unsigned int getSize();
    BigInt& operator<<=(unsigned int);
    BigInt& operator>>=(unsigned int);
    static std::pair<BigInt, BigInt> extended_gcd(BigInt a, BigInt b);
    BigInt getModuloPowerTwo(unsigned int);
};
