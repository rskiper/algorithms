/*	2102. MICHAEL AND CRYPTOGRAPHY (https://acm.timus.ru/problem.aspx?space=1&num=2102)
The hacker Michael develops breakthrough password manager, which is called KEK (Keeper of Encrypted Keys). A distinctive feature of KEK is excellent security. 
To achieve this, Michael had to develop innovative encryption scheme. For example, in the well-known RSA scheme the sum of prime powers in the factorization 
is equal to 2, whereas in Michael’s scheme this sum is equal to 20!
However, the current version of the KEK runs very slow. Michael has found out that the problem is in the function of checking a modulus for correctness. 
This function should take the number n and answer, whether the sum of prime powers included in the factorization of n is equal to 20. Can you do this quickly?
Remember that the factorization of an integer is the representation of it in the form like p1^α1 · p2^α2 · ... · pk^αk, where pi are prime numbers, and αi > 0. 
It is known that such representation is unique. Then the sum of powers looks like α1 + α2 + ... + αk.
Input: The only line contains an integer n (1 ≤ n ≤ 10^18)
Output: If the sum of prime powers, included in the factorization of n, is equal to 20, then output “Yes”, otherwise output “No”
*/

#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	__int64 n;
	cin >> n;
	int power_sum = 0;

	while (n % 2 == 0 && power_sum < 20)	//count for powers of 2
	{
		n /= 2;
		power_sum++;
	}
	
	while (n % 3 == 0 && power_sum < 20)	//count for powers of 3
	{
		n /= 3;
		power_sum++;
	}
	double max;
	if (power_sum >= 14)	//upper value for possible divisors satisfying the conditions
		max = sqrt(n);
	else
		max = pow(n, 1.0 / (14 - power_sum));
	int step = 4;	//using smart step for accelerated iteration over prome numbers
	for (__int64 i = 5; i <= max && n > 1 && power_sum < 20; i += step)	// count for powers of other prime dividers
	{
		while (n % i == 0)
		{
			n /= i;
			power_sum++;
		}
		step = (step == 4) ? 2 : 4;
	}

	if (n > 1)
		power_sum++;
	if (power_sum == 20)
		cout << "Yes";
	else
		cout << "No";
	return 0;
}

