#include "LongNumber.h"
#include <fstream>

bool test(unsigned int n);

template <typename T>
string NumberToString ( T Number )
{
	ostringstream ss;
	ss << hex << Number;
	return ss.str();
}

int main()
{
	//string a = "100000000";
	//string b = "1";
	//string n = "10000";
	//LongNumber num1(a), num2(b), num3(n), r(0), q(0);
	//cout << hex << "a = " << num1 << endl << "b = " << num2 << endl;
	//cout << a << " * " << b << " % " << n << " = " << LongNumber::Blackley(num1, num2, num3) << endl;
	//LongNumber::MonRed(num1, num2);
	/*
	cout <<"floor(a / b) = " << hex << num1 / num2 << endl;
	//cout << hex << "a % b = " << num1 % (num1 + LongNumber(1)) << endl;
	//q = LongNumber::Barrett(num1, num2);
	cout << "a % b = " << hex << q << endl;

	

	LongNumber num1("16bf74e84ae1388c2");
	LongNumber num2("192b3aeea62091fd9");
	LongNumber n("123456789");
	unsigned int c = LongNumber::Base - inverse(n.arr[0], LongNumber::Base);

	clock_t t1, t2;
	t1 = clock();
	for(int i = 0; i < 100; ++i)
	{
		LongNumber::MonRed(num1 * num2, n);
		LongNumber A;
		A.arr.resize(n.arr.size(), 0);
	}
	t1 = clock() - t1;
	printf ("It took me %d clicks (%f seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC);

	t2 = clock();
	for(int i = 0; i < 100; ++i) LongNumber::MonPro(num1, num2, n, c);
	t2 = clock() - t2;

	printf ("It took me %d clicks (%f seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC);
	*/

	//cout << "16 mod 5 = " << LongNumber::MonRed(LongNumber(21), LongNumber(5)) << endl;
	//cout << "2^3 mod 5 = " << LongNumber::MonPro(LongNumber(3), LongNumber(7), LongNumber(5)) << endl;
	//*/

	//LongNumber n("123456789");
	//LongNumber m_y = (LongNumber(1) <<= (BITSINWORD * n.getSize())) % n;
	//cout << "1 * R mod n = " << m_y << endl;
	//cout << "1 * R^-1 mod n = ";
	//cout << LongNumber::MonRed(LongNumber(1), n) << endl;
	//cout << "MonRed(R) = " << LongNumber::MonRed(m_y, n) << endl;
	//cout << "MonProd(R,R) = " << LongNumber::MonPro(m_y, m_y, n) << endl;
	//cout << "MonRed(R * R) = " << LongNumber::MonRed(m_y * m_y, n) << endl;
	
	/*
	
	//LongNumber abc1(a1), abc2(a2), abc3(0);
	LongNumber num1("FA815F0256BF177289043EA385FA858D3E9ABB3BD321B3A04DD958E9CB168D51F0E96A865D5AC90166870101AAAB44854CF1B4B797946BEB4A093DFEE039ED3139A2EEB9EE5C4623E6368B4F9D6A0581C755931198755B3188F9B5E9CA6FEF5A265481BDBAB2F0CB8C8AFADEA90311988BA6D2A25A7C8E902D70FF45EFE0F7CF");
	LongNumber num2("EF20E7D078DD8219D1B62893E7C49206C7CA3F441127FB209ABDF965E7C5A02356928D0451E733364C163F68E8EDEE576C3C492D9DA25D6BA53FD74C97CF8C741EB4C1EFD0CB647105D5296E84D6DA3D9E56F6970941030ED4A62EDBE163632F353FDCA88144BEE196643234F576A806B33DC22E6179AFF713D1DDDE89D408FB");
	//LongNumber num1("16bf74e84ae1388c2");
	//LongNumber num2("192b3aeea62091fd9");
	//LongNumber num3(0);
	*/

	clock_t t1 = clock();
	cout << "X^d mod N = " << LongNumber::MonPow(LongNumber("FA815F0256BF177289043EA385FA858D3E9ABB3BD321B3A04DD958E9CB168D51F0E96A865D5AC90166870101AAAB44854CF1B4B797946BEB4A093DFEE039ED3139A2EEB9EE5C4623E6368B4F9D6A0581C755931198755B3188F9B5E9CA6FEF5A265481BDBAB2F0CB8C8AFADEA90311988BA6D2A25A7C8E902D70FF45EFE0F7CF"), LongNumber("EF20E7D078DD8219D1B62893E7C49206C7CA3F441127FB209ABDF965E7C5A02356928D0451E733364C163F68E8EDEE576C3C492D9DA25D6BA53FD74C97CF8C741EB4C1EFD0CB647105D5296E84D6DA3D9E56F6970941030ED4A62EDBE163632F353FDCA88144BEE196643234F576A806B33DC22E6179AFF713D1DDDE89D408FB"), LongNumber("B5EA5D0686C36C6EAC9DC7446716C00712D1C2052B0AAAD6332F43C56940A696E5FC3FE0789EAD2777646B9FE39823BB80BDDA384EE2C5E000940D2BF03BE3F5DF06482E1BEED81FFBC77242E573F38D791644EF98FCE0F4195704A4DC1656AFE9E16C69F74373C724C4117CEE03F4C9BD31366F2B8E48672D4D361FC81154C9000")) << endl;	
	t1 = clock() - t1;
	printf ("It took me %d clicks (%f seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC);

	clock_t t2 = clock();
	//cout << "X^d mod N = " << LongNumber::Pow(LongNumber("FA815F0256BF177289043EA385FA858D3E9ABB3BD321B3A04DD958E9CB168D51F0E96A865D5AC90166870101AAAB44854CF1B4B797946BEB4A093DFEE039ED3139A2EEB9EE5C4623E6368B4F9D6A0581C755931198755B3188F9B5E9CA6FEF5A265481BDBAB2F0CB8C8AFADEA90311988BA6D2A25A7C8E902D70FF45EFE0F7CF"), LongNumber("EF20E7D078DD8219D1B62893E7C49206C7CA3F441127FB209ABDF965E7C5A02356928D0451E733364C163F68E8EDEE576C3C492D9DA25D6BA53FD74C97CF8C741EB4C1EFD0CB647105D5296E84D6DA3D9E56F6970941030ED4A62EDBE163632F353FDCA88144BEE196643234F576A806B33DC22E6179AFF713D1DDDE89D408FB"), LongNumber("B5EA5D0686C36C6EAC9DC7446716C00712D1C2052B0AAAD6332F43C56940A696E5FC3FE0789EAD2777646B9FE39823BB80BDDA384EE2C5E000940D2BF03BE3F5DF06482E1BEED81FFBC77242E573F38D791644EF98FCE0F4195704A4DC1656AFE9E16C69F74373C724C4117CEE03F4C9BD31366F2B8E48672D4D361FC81154C9")) << endl;	
	t2 = clock() - t2;
	printf ("It took me %d clicks (%f seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC);


	/*LongNumber a = LongNumber("940B4FC4B1899EE4CA5BCD0D8207B07E81B755841976CEDA5ED9C39BCF9F24B5");
	LongNumber n = LongNumber("6E85F7472955618F72176DB6593224B50DE07643953BAF84CC29AA4F813EDD6F");
	LongNumber mu = (LongNumber(1) <<= (2 * n.arr.size() * LongNumber::BitsInWord)) / n;
	cout << "mu = " << mu << endl;
	cout << LongNumber::Barrett(a, n, mu) << endl;*/

	//LongNumber a(35), b(51);

	//pair<LongNumber, LongNumber> uv = LongNumber::extended_gcd(a, b);

	//cout << "u = " << uv.first << " v = " << uv.second << endl;
	
	return 0;
}

bool test(unsigned int n)
{
	n = n / (sizeof(int) * 8);
	//srand (time(NULL));
	string a, b, c;
	for(size_t i = 0; i < n; ++i)
	{
		a += NumberToString(rand());
		b += NumberToString(rand());
		c += NumberToString(rand());

	}
	cout << "string a = " << a << endl;
	cout << "string b = " << b << endl;
	cout << "string c = " << c << endl;

	LongNumber n1(a), n2(b), n3(c);

	cout << hex << "LongNumber a = " << n1 << endl;
	cout << "LongNumber b = " << n2 << endl;
	cout << "LongNumber c = " << n3 << endl;

	cout << "(a + b) * c   = " << LongNumber((n1 + n2) * n3) << endl;
	cout << "c * (a + b)   = " << LongNumber(n3 * (n1 + n2)) << endl;
	cout << "a * c + b * c = " << LongNumber(n1 * n3 + n2 * n3) << endl;

	cout << endl;

	int k = rand() % 1000 + 100;
	LongNumber n4(k), n5(0);
	cout << dec << "n = " << n4 << endl;
	cout << "n * a = " << n4 * n1 << endl;
	for(int i = 0; i < k; ++i)
		n5 = n5 + n1;
	cout << "a + a + ... + a (n times) = " << n5 << endl;
	
	return true;
}