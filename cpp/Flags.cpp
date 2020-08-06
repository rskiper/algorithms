
/*
1225. Flags	(https://acm.timus.ru/problem.aspx?space=1&num=1225)
On the Day of the Flag of Russia a shop-owner decided to decorate the show-window of his shop with textile stripes of white, blue and red colors.
He wants to satisfy the following conditions:
1. Stripes of the same color cannot be placed next to each other.
2. A blue stripe must always be placed between a white and a red or between a red and a white one.
Determine the number of the ways to fulfill his wish.
Input: N, the number of the stripes, 1 ≤ N ≤ 45.
Output: M, the number of the ways to decorate the shop-window.
*/
#include <iostream>

using namespace std;

int main()
{
	//Surprisingly, required number for N flags is Fibonacci number Fib(N) with first two elements Fib(1)=Fib(2)=2 and can be found for O(N)
	int n;
	cin >> n;
	unsigned int a1, a2, t;
	a2 = a1 = 2;
	for (int i = 2; i < n; i++)
	{
		t = a2 + a1;
		a1 = a2;
		a2 = t;
	}
	cout << a2;
	return 0;
}