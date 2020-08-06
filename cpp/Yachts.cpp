/*1648. YACHTS (https://acm.timus.ru/problem.aspx?space=1&num=1648)
Everybody knows that the Yekaterinozavodsk Shipyard constructs the best yachts in the world. They are so popular that when a manufacturer becomes a billionaire,
he comes to the shipyard in the end of the same month to get a new yacht. You bet! The yachts are hand-made and their interior is made from a valuable 
red-black tree. Unfortunately, there are few workers at the shipyard, therefore, it can build no more than d new yachts per month. As a result, the shipyard 
sometimes cannot produce enough yachts for their customers. And those billionaires are quite impulsive people: if they come to the shipyard and there is no yacht 
for them, they abandon the whole idea of buying a yacht. Of course, the shipyard can produce yachts and store them somewhere for future use, but you should pay 
1 golden bar to store one yacht during one month.
The managers want to know the maximal number of yachts the shipyard can sell during the next n months, and the miminal number of golden bars which should be 
paid for the storage. The students from the Department of Economics of the Yekaterinozavodsk University predicted the amount of future billionaires in each of 
these n months. You should use this data to answer the managers' questions.

Input: The first line contain space-separated integers n and d (1 ≤ n ≤ 20000; 1 ≤ d ≤ 100000). 
The second line contains space-separated integers a1, a2, …, an. ai is the number of future billionaires in i-th month (0 ≤ ai ≤ 100000). 
Output: Two integers separated by space — the maximal number of yachts the shipyard can sell and the minimal number of golden bars 
required to pay for the storage. 
*/

#include <iostream>
#include <forward_list>
using namespace std;

struct Preorder
{
	int Number;
	int Month;
};

int main()
{
	int n, d;
	cin >> n >> d;
	int *a = new int[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];

	forward_list<Preorder> Preorders;	//list of orders which can't be satisfied right away and needed to be produced in advance
	//list is stack-based, so last orders will be produced firstly, and their storage cost is minimal

	__int64 store_pay = 0;	//storage price for pre-ordered yachts
	__int64 orders = 0;	//number of orders can be satisfied

	//count (store_pay) and (orders) by iteration over a[], so it will take about O(n)
	for (int i = n - 1; i >= 0; i--)
	{
		if (a[i] > d)	//number of orders at i-th month is more than allowed
		{
			Preorder p;
			p.Number = a[i] - d;	//create preorder for yachts can't be produced this month
			p.Month = i;
			Preorders.push_front(p);
			orders += d;
		}
		else
		if (a[i] < d)	//number of orders in i-th month is less and we can take some preorders
		{
			int k = d - a[i];
			while (k > 0 && !Preorders.empty())
			{
				Preorder p = Preorders.front();	//get last preorder
				if (k == p.Number)
				{
					store_pay += (p.Month - i) * k;
					Preorders.pop_front();
					k = 0;
				}
				else
				if (k < p.Number)	//we can fulfill preorder only partially
				{
					store_pay += (p.Month - i) * k;
					Preorders.pop_front();
					p.Number -= k;
					Preorders.push_front(p);	//push partially produced preorder back
					k = 0;
				}
				else	//if k > p.Number, we can fulfill next preorder
				{
					store_pay += (p.Month - i) * p.Number;
					k -= p.Number;
					Preorders.pop_front();
				}
			}
			orders += d - k;
		}
		else		//if a[i] == d
			orders += d;
	}
	cout << orders << " " << store_pay;

	return 0;
}

