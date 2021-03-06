#include "BigInt.h"

BigInt::BigInt() {
    nonNegative = 1;
}

BigInt::BigInt(unsigned int data)
{
    nonNegative = 1;
    arr.push_back(data);
}

BigInt::BigInt(const BigInt& data)
{
    nonNegative = data.nonNegative;
    arr.assign(data.arr.begin(), data.arr.end());
}

BigInt::BigInt(std::string str)
{
    nonNegative = 1;
    std::string buff;
    std::string::iterator itr = str.end(), end = str.begin();
    for(; itr - end >= sizeof(int) * 2; itr -= sizeof(int) * 2)
        arr.push_back(stoul(buff.assign(itr - sizeof(int) * 2, itr), nullptr, 16));
    if(itr > end)
        arr.push_back(stoul(buff.assign(end, itr), nullptr, 16));
    while(arr.size() > 1 && arr[arr.size() - 1] == 0) arr.pop_back();
}

std::ostream& operator<<(std::ostream& out, const BigInt& data)
{
    if(!data.nonNegative) out << '-';
    out << std::hex << data.arr[data.arr.size() - 1];
    for(int i = data.arr.size() - 2; i >= 0; --i)
        for(int j = sizeof(int) * 2 - 1; j >= 0; --j)
            out << ((data.arr[i] >> j * 4) & 0xf);
    return out;
}
