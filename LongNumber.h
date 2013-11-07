#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <utility>

#define BITSINWORD 32

using namespace std;

unsigned long long ext_gcd(unsigned long long a, unsigned long long b, long long& x, long long& y);
unsigned long long inverse(unsigned long long a, unsigned long long n);

class LongNumber
{
private:
	vector <unsigned int> arr;

	bool nonNegative;

	LongNumber& add(LongNumber&);
	LongNumber& sub(LongNumber&);
	pair<LongNumber, unsigned int> divByte(unsigned int&);
	static pair<LongNumber, LongNumber> div(LongNumber, LongNumber&);
	static unsigned int const c1 = 0x7fffffff;
	static unsigned long long const Base = 1ULL << sizeof(int) * 8;

public:

	//Base
	LongNumber();
	LongNumber(unsigned int);
	LongNumber(string);
	LongNumber(const LongNumber&);	
	friend ostream& operator<<(ostream&, const LongNumber&);


	//Logic
	friend bool operator<(const LongNumber&, const LongNumber&);
	friend bool operator==(LongNumber&, LongNumber&);
	friend bool operator==(const LongNumber&, unsigned int);


	//Arithmetic
	friend LongNumber operator+(LongNumber&, LongNumber&);
	friend LongNumber operator+(LongNumber&, unsigned int);
	friend LongNumber operator-(LongNumber&, LongNumber&);
	friend LongNumber operator*(LongNumber&, LongNumber&);
	friend LongNumber operator*(LongNumber, unsigned int);
	friend LongNumber operator/(LongNumber&, LongNumber&);
	friend LongNumber operator/(LongNumber&, unsigned int);
	friend LongNumber operator%(LongNumber&, LongNumber&);
	LongNumber Square();


	//Modular
	static LongNumber Barrett(LongNumber, LongNumber&, LongNumber&);
	static LongNumber MonRed(LongNumber, LongNumber&);
	static LongNumber MonPro(LongNumber&, LongNumber&, LongNumber&, unsigned int c = 0);
	static LongNumber MonPow(LongNumber&, LongNumber&, LongNumber);
	static LongNumber MonOddPow(LongNumber&, LongNumber&, LongNumber&);
	static LongNumber Pow(LongNumber&, LongNumber&, LongNumber&);

	//Other
	unsigned int getSize(){
		return arr.size();
	}
	
	LongNumber& operator<<=(unsigned int);
	LongNumber& operator>>=(unsigned int);
	static pair<LongNumber, LongNumber> extended_gcd(LongNumber a, LongNumber b);
	LongNumber getModuloPowerTwo(unsigned int);
};