
/* 1119. METRO (https://acm.timus.ru/problem.aspx?space=1&num=1119)
Many of SKB Kontur programmers like to get to work by Metro because the main office is situated quite close the station Uralmash. 
So, since a sedentary life requires active exercises off-duty, many of the staff — Nikifor among them — walk from their homes to Metro stations on foot.
Nikifor lives in a part of our city where streets form a grid of residential quarters. All the quarters are squares with side 100 meters.
A Metro entrance is situated at one of the crossroads. Nikifor starts his way from another crossroad which is south and west of the Metro entrance. 
Naturally, Nikifor, starting from his home, walks along the streets leading either to the north or to the east. On his way he may cross some quarters 
diagonally from their south-western corners to the north-eastern ones. Thus, some of the routes are shorter than others. 
Nikifor wonders, how long is the shortest route.
You are to write a program that will calculate the length of the shortest route from the south-western corner of the grid to the north-eastern one.

Input: There are two integers in the first line: N and M (0 < N,M ≤ 1000) — west-east and south-north sizes of the grid. 
Nikifor starts his way from a crossroad which is situated south-west of the quarter with coordinates (1, 1). A Metro station is situated 
north-east of the quarter with coordinates (N, M). 
The second input line contains a number K (0 ≤ K ≤ 100) which is a number of quarters that can be crossed diagonally. 
Then K lines with pairs of numbers separated with a space follow — these are the coordinates of those quarters.
Output: Length of the shortest route from Nikifor's home to the Metro station in meters, rounded to the integer amount of meters.
*/
#include <iostream>
using namespace std;

struct Cut
{
	int x;
	int y;
	int h = 0;
};

//Sorting by X for diagonally crossed quarters subarray; if X of some elements is equal - by Y
// *s - first element pointer, n - length, mid - previously calculated average value for elements in subarray
//Sorting based on Hoare's quick sort, mid is pivot
void QuickSort(Cut* s, int n, int mid)
{
	if (n == 2)	//terminal case, sorting of two elements
	{
		if ((s[0].x > s[1].x) || (s[0].x == s[1].x && s[0].y > s[1].y))
		{
			Cut t = s[1];
			s[1] = s[0];
			s[0] = t;
		}
		return;
	}
	if (n < 2)	//terminal case, last element
		return;

	Cut *sub = new Cut[n];	//operating array
	int l = 0;	//index of first blank element in left part of operating subarray, increases from 0 to middle
	int r = n - 1;	//index of first blank element in right part of operating array, decreases from (n-1) to middle
	int mid_l, mid_r;	//pivots for left and right parts of array
	mid_l = mid_r = 0;
	for (int i = 0; i < n; i++)
	{
		if (s[i].x>mid)	
		{
			sub[r] = s[i];	//put sortable element to right part
			mid_r += sub[r].x;
			r--;
		}
		else
		{
			sub[l] = s[i];	//put sortable element to left part
			mid_l += sub[l].x;
			l++;
		}
	}
	if (sub[0].x < sub[n - 1].x)	//check if array consists of equal elements
	{
		mid_l = mid_l / l;
		mid_r = mid_r / (n - l);
		QuickSort(sub, l, mid_l);	//recursively sorting for left part of operating subarray
		QuickSort(sub + l, n - l, mid_r);	//recursively sorting for right part of operating subarray

		for (int i = 0; i < n; i++)	//copy sorted elements from operating array back to outer array
			s[i] = sub[i];
	}

}

int main()
{
	int ox, oy, k;
	cin >> ox >> oy;
	cin >> k;

	int mid = 0;
	Cut *s = new Cut[k];	//array of quarters that can be crossed diagonally
	for (int i = 0; i < k; i++)
	{
		cin >> s[i].x >> s[i].y;
		mid += s[i].x;
	}
	if (k>0)
	{
		mid = mid / k;	//calculate average value for X, it will be pivot for quick sort
		QuickSort(s, k, mid);	
		//sorting array by X, in this way all diagonally crossed quarters are located: 
		//nearest to SW corner at the beginning, nearest to NE corner at the end of the array
	}
	//for minimizing length of route we should maximize number of diagonally crossed quarters
	for (int i = 0; i < k; i++)	//we iterating over quarters in array
	{
		int max = 0;
		//for each one we're looking for an quarter to the left and below, which can be achieved with maximal number of diagonally crossed quarters
		//it's already calculated for j-th quarters, j<i, because we moving from left to right and all elements in array are sorted
		for (int j = i - 1; j > 0; j--)
		{
			if (s[j].x < s[i].x && s[j].y < s[i].y && s[j].h >= s[max].h)
				max = j;
		}
		//in this way, we found the greatest number of diagonally crossed quarters for i-th element in array
		if (s[i].x > s[max].x && s[i].y > s[max].y)
			s[i].h = s[max].h + 1;
		else
			s[i].h = 1;
	}

	int c = 0;
	for (int i = 0; i < k; i++)	//looking for greatest number for the whole array finally
	{
		if (s[i].h > c)
			c = s[i].h;
	}

	// length of route is a sum of quarters passed along their border plus diagonally crossed quarters
	double distance = (ox + oy - c * 2) * 100 + c * 100 * sqrt(2);
	cout << round(distance);

	return 0;
}