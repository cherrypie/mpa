#include "LongNumber.h"

bool operator<(const LongNumber& a, const LongNumber& b)
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

bool operator==(LongNumber& a, LongNumber& b)
{
	if(a.arr.size() != b.arr.size())
		return false;
	for(size_t i = 0; i < a.arr.size(); ++i)
		if(a.arr[i] != b.arr[i])
			return false;
	return true;
}

bool operator==(const LongNumber& a, unsigned b)
{
	if(a.arr.size() != 1)
		return false;
	else if(a.arr[0] != b)
		return false;
	return true;
}