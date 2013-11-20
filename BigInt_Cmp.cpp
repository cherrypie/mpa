#include "BigInt.h"

bool operator<(BigInt& a, BigInt& b)
{
    if(a.arr.size() < b.arr.size())
        return true;
    else if(a.arr.size() > b.arr.size())
        return false;
    else
    {
        for(int i = a.arr.size() - 1; i >= 0; --i)
        {
            if(a.arr[i] < b.arr[i])
                return true;
            else if(a.arr[i] > b.arr[i])
                return false;
        }
    }
    return false;
}

bool operator==(BigInt& a, BigInt& b)
{
    if(a.arr.size() != b.arr.size())
        return false;
    for(size_t i = 0; i < a.arr.size(); ++i)
        if(a.arr[i] != b.arr[i])
            return false;
    return true;
}
