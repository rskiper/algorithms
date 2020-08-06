/*1012. K-based Numbers. Version 2
(https://acm.timus.ru/problem.aspx?space=1&num=1012)
Let’s consider K-based numbers, containing exactly N digits. We define a number to be valid if its K-based notation doesn’t contain two successive zeros.
For example:
1010230 is a valid 7-digit number;
1000198 is not a valid number;
0001235 is not a 7-digit number, it is a 4-digit number.

Given two numbers N and K, you are to calculate an amount of valid K based numbers, containing N digits.
You may assume that 2 <= K <= 10; N >= 2; N + K <= 1800.
Input: The numbers N and K in decimal notation separated by the line break.
Output: The result in decimal notation.
*/
#include "stdafx.h"
#include <iostream>
using namespace std;


class ExtraLong2	//the class partially implements arbitrary-precision arithmetic according to the needs of problem
{
private:
	char *s;	//long numbers realized as char array of length n, and digits are in reverse order, so s[0] is the least significant digit
		//thereby the bit depth of the number can be ignored
	int _n;
	int last;	//index of the most significant digit of the number

public:
	char* GetLink()
	{
		return s;
	}

	ExtraLong2(int n)	//constructor initializes zero number with length n
	{
		_n = n;
		s = new char[n];
		last = 0;
		s[0] = 0;
		for (int i = 0; i < n; i++)
			s[i] = 0;
	}

	int Length()
	{
		return last + 1;
	}

	char* Get()
	{
		char* res = new char[_n];
		int j;
		for (int i = last, j = 0; i >= 0; i--, j++)
			res[i] = s[j];
		return res;
	}

	void Set(unsigned __int64 number)	//assigning spesified number
	{
		last = -1;
		while (number > 0 && last<_n)
		{
			last++;
			s[last] = number % 10;
			number = number / 10;
		}
	}


	void Add(ExtraLong2 b)	//adding another ExtraLong2 number
	{
		char* bs = b.GetLink();
		int b_length = b.Length();
		char rest = 0;
		int i = 0;
		for (i; i < b_length; i++)	//add the digits of the second term
		{
			rest = s[i] + bs[i] + rest;
			s[i] = rest % 10;
			rest = rest / 10;
		}
		while (rest > 0)	//drop the rest to higher digits, if it's needed
		{
			s[i] += rest % 10;
			rest = rest / 10;
			i++;
		}
		if (last < i - 1)	//update index of the most important digit, if it's needed
			last = i - 1;
	}

	void Multiply(int b)	// multiplication by b, 1 <= b <= 9
	{
		if (b > 9)
			return;
		int rest = 0;
		int i = 0;
		for (i; i <= last; i++)
		{
			rest = rest + s[i] * b;	//multiply all digits by b
			s[i] = rest % 10;
			rest = rest / 10;
		}

		while (rest > 0)
		{
			s[i] = rest % 10;	//drop the rest
			rest = rest / 10;
			i++;
		}
		if (last < i - 1)
			last = i - 1;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{

	int n, k;
	cin >> n;	//digits
	cin >> k;	//base

	{
		ExtraLong2 zero0(n);
		zero0.Set(1);	//number of cases when 0 is in this position(except most significant digit)
		ExtraLong2 nonzero0(n);
		nonzero0.Set(k - 1);	//number of cases when it's not '0'
		ExtraLong2 zero1(n);
		ExtraLong2 nonzero1(n);

		//count the number of possible allocations for k-based digits in i-digit number, using value for (i-1)-digit number, counted earlier
		for (int i = 2; i <= n; i++)
		{
			zero1 = nonzero0;	//'0' can be in new digit only if next digit is not '0'
			nonzero1 = zero0;	//number of allocations when new digit is not '0': nonzero1=(zero0+nonzero0)*(k-1)
			nonzero1.Add(nonzero0);
			nonzero1.Multiply(k - 1);

			zero0 = zero1;
			nonzero0 = nonzero1;
		}

		char* r = nonzero0.Get();
		for (int j = 0; j < nonzero0.Length(); j++)	//printing the result
			cout << (int)r[j];
	}
	return 0;
}