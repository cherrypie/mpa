#include "BigInt.h"
#include <chrono>
#include <random>

using std::cout;
using std::endl;
using namespace std::chrono;

BigInt getRandomBigInteger(unsigned int words)
{
    BigInt a;
    a.arr.clear();

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<unsigned int> distribution(0, 0xffffffff);

    for(size_t i = 0; i < words; ++i)
        a.arr.push_back(distribution(generator));

    while(a.getSize() > 1 && a.arr[a.getSize() - 1] == 0)
        a.arr.pop_back();

    return a;
}

double timeOnRandMonExp(unsigned int word, unsigned int times)
{
    high_resolution_clock::time_point t1, t2;
    t1 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t1 - t1);
    BigInt x, d, n;
    for(size_t i = 0; i < times; ++i)
    {
        x = getRandomBigInteger(word);
        d = getRandomBigInteger(word);
        n = getRandomBigInteger(word);

        //n.arr[0] |= 1;
        n.arr[0] &= 0xfffffffe;

        t1 = high_resolution_clock::now();
        BigInt::MonPow(x, d, n);
        t2 = high_resolution_clock::now();
        time_span += duration_cast<duration<double>>(t2 - t1);
    }

    return time_span.count() / times;
}

int main(void)
{
    BigInt a("5B95EAFF298E8548D1BDC263C3442647E775632AE8234CC77E7816B1DD757F742A83D45B3CFE729E59E1573AFB56D3517BA4E2527807E48F39AE6E712BD432C47995D0881C429EA2DA3227647DAB9D2CC6A3A46822C5925973141FED6AF8F21C31F3A58057839CB05B4153CE541573260993F4DA5137786275485882DF4A3613");
    BigInt b("DBA4984D68D681DA1B9CC0FAA9B9DE6624623C770C8629856489AE9C581E859BBC147287BFF6CE738D988FEA39839D1884858126603095467AED2403ADCE2EB0F59086EEC5902654DF77603EE8B1CA61C011B6C2A47611122B297B4CA6BF82B743202590124C6C6100D82ACF1B1E7AB239643466C561CBE37F65322B55F73C36");
    BigInt n("318E6E1097778B5112F905160C41E2485EF5F1BBEC94DC8AAEF3C7ACAAEEA4938CB594A40E5D1A89943ED68102AFDEE86698AEFF5252928C36CA3DEC540417E32973FED8A80CEABBC8CEE71FCE8636BD894385C1ACB428D2AD103DF8A1850A4715EFD5BC6D0A38659D7BBF844E36D51B8E41193CB1E2CC69A4E4E348FAE3C985");
    BigInt r1, r2;

    //BigInt a("161C3B146C62");
    //BigInt b("C0AF61D5E646");
    //BigInt n("B011DD7C0B9E");

    /*
    cout << "a =     " << a << endl;
    cout << "b =     " << b << endl;
    cout << "n =     " << n << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;


    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    r1 = BigInt::Pow(a, b, n);
    cout << r1 << endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds." << std::endl;

    t1 = high_resolution_clock::now();
    r2 = BigInt::MonPow(a, b, n);
    cout << r2 << endl;
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds." << std::endl;

    if(r1 == r2)
        cout << "All is correct!\n";

    */

    for(unsigned int i = 1; i <= 512; i <<= 1)
        cout << i << '\t' << timeOnRandMonExp(i, 2 + 64 / i) << endl;

	return 0;
}
