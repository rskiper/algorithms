/*1635. Mnemonics and Palindromes
(original problem description: https://acm.timus.ru/problem.aspx?space=1&num=1635)
In short, the problem is to find the minimum sequence of palindromes, that completely covers the input string, and out number of palindromes and its sequence.
Input: In the first line there is the string. This is a nonempty line consisting of lowercase English letters. The length of the line is at most 4000 symbols.
Output: In the first line output the minimal number of palindromes to which the input string can be decomposed. 
In the second line output palindromes from the optimal decomposition separated by a space. If several answers are possible, output any of them.
For example: "abzzbbbzza" -> "a b zzbbbzz a"
*/

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string name;
	cin >> name;
	__int16 length = name.length();
	__int16 i, j;
	__int16* radii[2];	//here we collect maximal radii of palindromes for each char in the string, even and odd separately
	radii[0] = new __int16[length];	//subarray for even palindromes, radii[0][i]>0, if name[i]==name[i+1]
	radii[1] = new __int16[length];	//subarray for odd palindromes, radii[1][i]>0, if name[i-1]==name[i+1]
	__int16* weights = new __int16[length];	//operating array for char's weights, 
											//where weight of i-th char is minimal amount of palindromes in substring starting at the i-th char
	__int16* links = new __int16[length];	//links to last symbol in largest palindrome starting at the i-th char
	for (i = 0; i < length; i++)
	{
		radii[0][i] = radii[1][i] = weights[i] = 0;
		links[i] = i;
	}

	__int16 c, rright, center, parity_flag;
	center = c = 0;	//center - index of base palindrome center, where base palindrome is the palindrome that includes the current substring, c - index of current char
	rright = -1; //rright - right border of base palindrome

	parity_flag = -1;	//parity of base palindrome: 0 - even, 1 - odd
	//base palindrome is used for Manaker algorithm
	while (c < length - 1)	//now let's find all palindromes in string
	{
		__int16 r = 0;
		//Manaker's algorithm for even palindromes
		if (c < rright)	
		{
			r = ((rright - c) < radii[0][2 * center - c - parity_flag]) ? (rright - c) : radii[0][2 * center - c - parity_flag];
			//distance to the right border of base palindrome limits radius of symmetric palindrome
			if (r>0)
				r -= 1 - parity_flag;	//if base palindrome is even, then radius of symmetric palindrome is 1 more
			for (int k = c - r + 1; k < c; k++)
			{
				if (links[k] < c)	//we temporarily use links array to store center's index of largest palindrome containing the current char
					links[k] = c;
			}
		}
		while (c - r >= 0 && c + r + 1 < length && name[c - r] == name[c + r + 1])	//trying to increase radius to maximum possible
		{
			r++;
			if (links[c - r + 1] < c)
				links[c - r + 1] = c;
		}
		radii[0][c] = r;
		if (r>0 && c + r > rright)	//if right border of current palindrome is further than the base one, then replace base palindrome with the this one
		{
			rright = c + radii[0][c];
			center = c;
			parity_flag = 0;
		}

		//similarly find the largest odd palindrome
		r = 0;
		if (c < rright)
		{
			r = ((rright - c) < radii[1][2 * center - c + 1 - parity_flag]) ? (rright - c) : radii[1][2 * center - c + 1 - parity_flag];
			if (r>0)
				r -= 1 - parity_flag;
			for (int k = c - r; k < c; k++)
			if (links[k] < c) 
				links[k] = c;
		}
		while (c - r - 1 >= 0 && c + r + 1 < length && name[c - r - 1] == name[c + r + 1])
		{
			r++;
			if (links[c - r] < c)
				links[c - r] = c;
		}
		radii[1][c] = r;
		if (c + radii[1][c]>rright)	//check for right border of current odd palindrome
		{
			rright = c + radii[1][c];
			center = c;
			parity_flag = 1;
		}
		c++;
	}
	
	//all palindromes are found, now we're looking for minimal palindrome sequences for all substrings [i; length-1]
	weights[length - 1] = 1;	//initialize weight of latest char in the string
	for (i = length - 2; i >= 0; i--)	, 
	{
		__int16 min = weights[i + 1] + 1;	//if here's no palindrome starts from i symbol, weight[i] equal to weight of the next char +1
		__int16 last = i;
		j = links[i];	//the farthest(to the end of the string) palindrome containing i-th char
		while (j >= i && min > 1)	//looking for palindrome containing i-th char and having minimum weight
		{
			__int16 right;
			if (radii[1][j] >= j - i)	//check odd palindrome
			{
				right = 2 * j - i + 1;	//index of right border of the palindrome
				if (right < length)
				{
					if (min > 1 + weights[right])
					{
						min = 1 + weights[right];
						last = right - 1;	//saving the last char of the palindrome to links[i]
					}
				}
				else
				{	//palindrome contains the end of string
					min = 1;
					last = right - 1;	
				}
			}
			if (radii[0][j] >= j - i + 1)	//check even palindrome
			{
				right = 2 * j - i + 2;	//index of right border of the palindrome
				if (right < length)
				{
					if (min>1 + weights[right])
					{
						min = 1 + weights[right];
						last = right - 1;	//saving the last char of the palindrome to links[i]
					}
				}
				else
				{	//palindrome contains the end of string
					min = 1;
					last = right - 1;
				}
			}
			j--;
		}
		weights[i] = min;	//store weight and link
		links[i] = last;
	}

	string res = "";
	i = 0;
	while (i < length)	//compose the answer by iterating over the chain starting from 0-th char
	{
		for (j = i; j <= links[i]; j++)
			res += name[j];
		if ((i = j) < length)
			res += " ";
	}
	cout << weights[0] << endl;
	cout << res;

	return 0;
}

