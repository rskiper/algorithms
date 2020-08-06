/*	1117. HIERARCHY 
* (original problem's description: http://acm.timus.ru/problem.aspx?space=1&num=1117)
* The employee reporting structure is a complete binary tree. Leaf numbers (ordinary employees) are a sequence of odd numbers, node numbers are even numbers, 
* with all descendants on the left having lower numbers than the node, and descendants on the right having higher numbers than the node.
* There are special system of intracorporate message exchange: a message from an employee with the number i can be addressed directly 
* only to the employees i-1 and i+1. This is done the same day (it takes 0 days to do that) if the employees are direct superior and subordinate,
* otherwise, the message delivery takes an amount of days that is equal to the number of intermediate employees between the sender and recipient.

* Input : The only line contains two positive integers : the number of an employee who sends a message and the number of the recipient.
* Each of the numbers doesn't exceed (2^31)-1.
* Output : You should output the only number — the number of days necessary to deliver the message.
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hierarchy
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] s = Console.ReadLine().Split(' ');
            uint m, n;
            m = Convert.ToUInt32(s[0]);
            n = Convert.ToUInt32(s[1]);
            if (m == n)
            {
                Console.WriteLine(0);
                return;
            }

            if (n < m)
            {
                uint r = n;
                n = m;      //it doesn't matter who is sender and recipient, distance is the same, so let sender will be less than recipient
                m = r;
            }


            //In this tree the numbers of nodes located at the same level contain same power of 2, which is equal to distance from leafs
            //Pure powers of two are located along the leftmost branch and include the topmost node in any subtree.
            //Distance between any two nodes is sum of distances between all even nodes and leafs within [m;n]
            //except nodes which is multiple of 2^1 only, i.e. direct parents of leafs
            uint days = 0;  //count for days needed to receive message from m to n
            uint power = 2; //count for power of 2
            uint e2 = 4;    //2 powered to power value
            //Iterate over powers of 2 and count the number of nodes that are multiples of it, between m and n
            while (e2 <= n)
            {
                uint first = 0; //first node which is multiple of e2
                uint last = 0;  //last node which is multiple of e2
                uint i = 0;
                if ((m % e2 == 0) && (m % (2 * e2) != 0))   //If m is a multiple of this power of 2
                {
                    days += (power - 1);   //then we pass the distance to leaf only 1 time, down.
                    i = 2 + m / e2;     //Addind 2 for count nodes are strictly within the interval
                }
                else
                    i = 1 + m / e2; //Find node first after m, which is multiple of this power of 2
                while (i % 2 == 0 && (i + 1) * e2 < n)  //no need for multiples of powers of two greater than e2
                    i++;
                first = i * e2; //Found the minimal node number which is multiple exactly of this power of 2 and located strictly within the interval (m; n)

                if ((n % e2 == 0) && (n % (2 * e2) != 0))   //Similarly for n
                {
                    days += (power - 1);
                    i = n / e2 - 1;
                }
                else
                    i = n / e2;
                while (i % 2 == 0 && i * e2 > m)
                    i--;
                last = i * e2;  //Found the maximal node number which is multiple exactly of this power of 2 and located strictly within the interval (m; n)

                if (first <= last)  //Collisions are possible for short intervals (m; n)
                {                   //Count for amount of nodes which is multiple exactly of this power of 2 and located strictly within the interval (m; n)
                    uint k = (last - first) / (2 * e2) + 1; //number of nodes which is multiple of e2 power of 2
                    days += k * (power - 1) * 2;   //power-1 - distance to leaf and number of days needed to delivery message
                    //Node is strictly internal, therefore this distance shound be passed there and back
                }
                e2 *= 2;
                power++;
            }
            Console.WriteLine(days);
            return;
        }
    }
}