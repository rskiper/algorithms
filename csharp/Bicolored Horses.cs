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

using System;
using System.Collections.Generic;


namespace BW_Horses
{
    class Program
    {
        static List<int> HorseGroups;   //All horse groups are grouped by color so they alternate: black-white-black-...

        static int k;   //total number of stables
        static int mm;   //number of horse's groups without personal stable
        static int[,] optimal_allocations; //x - number of first group in subset, y - number of unplased groups, value - minimal price for placing

        /*
         * Function finds optimal allocation for groups in HorseGroups, starting from (first), with (m) unplaced groups.
         * Once calculated, value is stored to array. Result for entire set will be stored in [0, mm-1] cell.
         */
        static int FindOptimal(int first, int m)
        {
            int white = 0, black = 0;   //counts for white and black horses joined right now
            bool parity = first % 2 == 0;   //variable to separate black and white groups, alternating one after another
            if (HorseGroups.Count - first - m == 1) //terminal case of recursion when only 1 stable is available
            {
                for (int i = 0; i <= m; i++, parity = !parity)
                    if (parity)
                        white += HorseGroups[first + i];
                    else
                        black += HorseGroups[first + i];
                return (optimal_allocations[first, m - 1] = white * black);
            }

            int s;  //temporary variable for current value
            int min = 62500;    //minimal umhappiness, will be returned by function

            /*Iterating over joining (joined) groups starting from (first) group,
             * then find optimal allocation for rest (m-joined-1) unplaced groups starting from (first+joined+1) recursively, with saving result to array
             */
            for (int joined = 0; joined <= m; joined++ )
            {
                if (parity) //trying to join first (joined) groups
                    white += HorseGroups[first + joined];
                else
                    black += HorseGroups[first + joined];
                s = white * black;

                if (joined < m) //finding optimal allocation for rest (m-joined-1) groups
                {   //if it was found once, the value is taken from array without function calling
                    s += (optimal_allocations[first + joined + 1, m - joined - 1] > 0) ?
                        optimal_allocations[first + joined + 1, m - joined - 1] : FindOptimal(first + joined + 1, m - joined);
                }

                if (s < min)    //minimize unhappiness
                    min = s;

                parity = !parity;
            }
            return (optimal_allocations[first, m - 1] = min);   //store result to array
        }

        static void Main(string[] args)
        {
            int n;  //total number of horses
            string[] a = Console.ReadLine().Split();    //read N and K
            n = Convert.ToInt32(a[0]);
            k = Convert.ToInt32(a[1]);
            HorseGroups = new List<int>();
            int prev = -1;
            for (int i = 0; i < n; i++) //fill HorseGroups
            {
                if (Convert.ToInt16(Console.ReadLine()) == 1)   //it's black horse
                {
                    if (HorseGroups.Count > 0 && prev == 1)
                        HorseGroups[HorseGroups.Count - 1]++;
                    else
                    {
                        HorseGroups.Add(1);
                        prev = 1;
                    }
                }
                else    //it's white horse
                {
                    if (HorseGroups.Count > 0 && prev == 0)
                        HorseGroups[HorseGroups.Count - 1]++;
                    else
                    {
                        HorseGroups.Add(1);
                        prev = 0;
                    }
                }
            }
            mm = HorseGroups.Count - k; //amount of horse's groups without personal stable, we need to mix them with other groups
            if (mm > 0)
            {
                optimal_allocations = new int[HorseGroups.Count, mm];
                FindOptimal(0, mm);
                Console.WriteLine(optimal_allocations[0, mm - 1]);
            }
            else
                Console.WriteLine(0);   //all group have it's personal stable, everyone is happy
        }

    }
}
