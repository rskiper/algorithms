/*  1073. Square Country (https://acm.timus.ru/problem.aspx?space=1&num=1073)
* There live square people in a square country. Everything in this country is square also. Thus, the Square Parliament has passed a law about a land. 
* According to the law each citizen of the country has a right to buy land. A land is sold in squares, surely. 
* Moreover, a length of a square side must be a positive integer amount of meters. Buying a square of land with a side a one pays a2 quadrics (a local currency) 
* and gets a square certificate of a landowner.
* One citizen of the country has decided to invest all of his N quadrics into the land. He can, surely, do it, buying square pieces 1 × 1 meters. 
* At the same time the citizen has requested to minimize an amount of pieces he buys: "It will be easier for me to pay taxes," — he has said. 
* He has bought the land successfully.
* Your task is to find out a number of certificates he has gotten.
* 
* Input: The only line contains a positive integer N ≤ 60 000 , that is a number of quadrics that the citizen has invested.
* Output: The only line contains a number of certificates that he has gotten.
*/
using System;
using System.Collections.Generic;

namespace SquareCountry
{
    class Program
    {
        static List<int> Squares = new List<int>(); //array with squares of numbers [1; sqrt(n)] to speed up calculations
        static int num;
        static int[] amount;

        //Recursive function to calculate number of squares to which n decomposes
        static int SteadAmount(int n)
        {
            if (Math.Sqrt(n) % 1 == 0)  //n is square already
                return 1;

            int min = n;
            int rest = 0;
            int k = 0;
            int i = 0;
            while (i < Squares.Count - 1 && Squares[i + 1] < n) //search for index of greatest square less than n
                i++;
            while ((i >= 0) && (3 * Squares[i] >= n))   //iterate over only greatest 2/3 of squares
            {
                rest = n - Squares[i];
                //calling recursive function for rest only if it wasn't calculated already
                k = (amount[rest - 1] == 0) ? amount[rest - 1] = SteadAmount(rest) : amount[rest - 1];  //rest-1 because indexing in amount[] starts from 0

                if (k < min)
                    min = k + 1;

                i--;
            }
            return min;
        }

        static void Main(string[] args)
        {
            num = Convert.ToInt32(Console.ReadLine());
            amount = new int[num];
            double sn = Math.Sqrt(num);
            if (sn % 1 == 0)    //number is already square
            {
                Console.WriteLine(1);
                return;
            }

            for (int i = 1; i <= sn; i++)   //fill array with squares
                Squares.Add(i * i);

            Console.WriteLine(SteadAmount(num));
            return;
        }
    }
}
