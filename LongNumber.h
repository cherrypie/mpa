#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <stdio.h>

#define BITSINWORD 32

class LongNumber
{
public:
	std::vector <unsigned int> arr;

	bool nonNegative;

	LongNumber& add(LongNumber&);
	LongNumber& sub(LongNumber&);
	std::pair<LongNumber, unsigned int> divByte(unsigned int&);
	static std::pair<LongNumber, LongNumber> div(LongNumber, LongNumber&);
	static unsigned int const c1 = 0x7fffffff;
	static unsigned long long const Base = 1ULL << sizeof(int) * 8;

public:

	//Input/Output
	LongNumber();
	LongNumber(unsigned int);
	LongNumber(std::string);
	LongNumber(const LongNumber&);	
    friend std::ostream& operator<<(std::ostream&, const LongNumber&);


	//Comparison operators
	friend bool operator<(LongNumber&, LongNumber&);
	friend bool operator==(LongNumber&, LongNumber&);


	//Arithmetic operations
	friend LongNumber operator+(LongNumber&, LongNumber&);
	friend LongNumber operator+(LongNumber&, unsigned int);
	friend LongNumber operator-(LongNumber&, LongNumber&);
	friend LongNumber operator*(LongNumber&, LongNumber&);
	friend LongNumber operator*(LongNumber&, unsigned int); //what a hack was here in prev version?
	friend LongNumber operator/(LongNumber&, LongNumber&);
	friend LongNumber operator/(LongNumber&, unsigned int);
	friend LongNumber operator%(LongNumber&, LongNumber&);
	LongNumber Square();


	//Modular operations
	static LongNumber Barrett(LongNumber, LongNumber&, LongNumber&);
	static LongNumber MonRed(LongNumber, LongNumber&);
	static LongNumber MonPro(LongNumber&, LongNumber&, LongNumber&, unsigned int c = 0);
	static LongNumber MonPow(LongNumber&, LongNumber&, LongNumber);
	static LongNumber MonOddPow(LongNumber&, LongNumber&, LongNumber&);
	static LongNumber Pow(LongNumber&, LongNumber&, LongNumber&);

	//Other stuff
	unsigned int getSize(){
		return arr.size();
	}
	
	LongNumber& operator<<=(unsigned int);
	LongNumber& operator>>=(unsigned int);
    static std::pair<LongNumber, LongNumber> extended_gcd(LongNumber a, LongNumber b);
	LongNumber getModuloPowerTwo(unsigned int);
};
