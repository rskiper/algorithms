/*
* 1167. Bicolored horses (https://acm.timus.ru/problem.aspx?space=1&num=1167)
* Every day, farmer Ion (this is a Romanian name) takes out all his horses, so they may run and play.
* When they are done, farmer Ion has to take all the horses back to the stables. In order to do this,
* he places them in a straight line and they follow him to the stables. Because they are very tired,
* farmer Ion decides that he doesn't want to make the horses move more than they should. So he develops
* this algorithm: he places the 1st P1 horses in the first stable, the next P2 in the 2nd stable and so on.
* Moreover, he doesn't want any of the K stables he owns to be empty, and no horse must be left outside.
* Now you should know that farmer Ion only has black or white horses, which don't really get along too well.
* If there are i black horses and j white horses in one stable, then the coefficient of unhappiness of that stable is i*j.
* The total coefficient of unhappiness is the sum of the coefficients of unhappiness of every of the K stables.
*
* Determine a way to place the N horses into the K stables, so that the total coefficient of unhappiness is minimized.
*
* Input: On the 1st line there are 2 numbers: N (1 ≤ N ≤ 500) and K (1 ≤ K ≤ N). On the next N lines there are N numbers.
* The i-th of these lines contains the color of the i-th horse in the sequence: 1 means that the horse is black, 0 means that the horse is white.
* Output: You should only output a single number, which is the minimum possible value for the total coefficient of unhappiness.
*/

#include <iostream>
#include <list>
using namespace std;

int* horses;	//Dynamic array with numbers of horses grouped by color, in [i] group
int g;	//amount of groups - size of horses[] array
int k;	//amount of stables
int mm;	//number of horse's groups without personal stable
int** optimal_allocations;

/*
* Function finds optimal allocation for groups in horses[], starting from (first), with (m) unplaced groups.
* Once calculated, value is stored to array. Result for entire set will be stored in [0, mm-1] cell.
*/
int FindOptimal(int first, int m)
{
	int white, black;	//counts for white and black horses joined right now
	white = black = 0;
	bool parity = false;	//variable to separate black and white groups, alternating one after another
	if (g - first - m == 1)	//terminal case of recursion when only 1 stable is available for placement
	{
		for (int i = 0; i <= m; i++)
		{
			if (parity)
				white += horses[first + i];
			else
				black += horses[first + i];
			parity = !parity;
		}
		return (optimal_allocations[first][m - 1] = white*black);
	}

	int min = 62500;	//minimal umhappiness, will be returned by function
	int	s;	//temporary variable for current value
	/*Iterating over joining (joined) groups starting from (first) group,
	* then find optimal allocation for rest (m-joined-1) unplaced groups starting from (first+joined+1) recursively, with saving result to array
	*/
	for (int joined = 0; joined <= m; joined++)
	{
		if (parity)	//trying to join first (joined) groups
			white += horses[first + joined];
		else
			black += horses[first + joined];

		s = white*black;
		if (joined < m)	//finding optimal allocation for rest (m-joined-1) groups
		{	//if it was found once, the value is taken from array without function calling
			s += (optimal_accocations[first + joined + 1][m - joined - 1]>0) ?
				optimal_allocations[first + joined + 1][m - joined - 1] : FindOptimal(first + joined + 1, m - joined);
		}

		if (s < min)	//minimize unhappiness
			min = s;

		parity = !parity;

	}
	return (optimal_allocations[first][m - 1] = min);	//store result to array
}

int main()
{
	list<int> grouping;	//temporary list for grouping horses by color
	//Horse's colors in queue alternate one after another, therefore we can optimize algorithm by grouping horses by color and count size of each group
	int n, h;
	cin >> n >> k;
	int prev = -1;
	for (int i = 0; i < n; i++)
	{
		cin >> h;
		if (h == prev)	//if next horse have same color as previous
			(*--grouping.end())++;	//increment number of horses in the last group
		else
		{
			grouping.push_back(1);	//else add new group
			prev = h;
		}
	}
	g = grouping.size();	//amount of groups is now known
	horses = new int[g];	//so we can initialize dynamic array for faster calculations
	h = 0;
	for (int p : grouping)	//copying values from list to dynamic array
		horses[h++] = p;
	
	mm = g - k;	//amount of horse's groups without personal stable, we need to mix them with other groups
	int res = 0;	//if all group have it's personal stable, everyone is happy
	if (mm > 0)	//else find optimal allocation
	{
		optimal_allocations = new int*[g];	//initialize dynamic array for saving temporary values of recursive function
		for (int i = 0; i < g; i++)
			optimal_allocations[i] = new int[mm]();

		res = FindOptimal(0, mm);
	}
	cout << res;
	return 0;
}