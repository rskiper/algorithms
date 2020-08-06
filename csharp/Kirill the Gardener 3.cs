/*2072. Kirill the Gardener 3
 * (https://acm.timus.ru/problem.aspx?space=1&num=2072)
 * Kirill the gardener has got a new task. He has to water the flowers growing on the huge flowerbed! It should be mentioned that the bed is very long 
 * and narrow at the same time. So from bird’s-eye view (and Kirill growth too) it looks like a straight line, where n points-flowers are located at 
 * regular intervals. For this job Kirill has a watering pot of infinite volume and smartwatch that shows moisture content of each flower before watering. 
 * The watering takes too much time, so the most dried flowers can die, which is unacceptable. So Kirill decided to water the flowers in order of their 
 * non-decreasing dryness. On the other hand, he wants to finish the watering as soon as possible, because there are a lot of other interesting things.
 * Assume that watering of one flower and walking between two neighbor flowers takes Kirill one minute. Can you figure out the time in which the young gardener 
 * will complete his job if he acts optimally? Initially Kirill stands near the leftmost flower.
 * Input: The first line contains an integer n (1 ≤ n ≤ 105) — it’s amount of flowers in the flowerbed. The second line contains n integers separated 
 * by spaces — it‘s moisture content of flowers given in order of their positions in the flowerbed from left to right. Moisture content is an integer 
 * from 1 up to 109 (including both).
 * Output: In the only line print an integer — the minimal time in which Kirill would complete watering.
 */
using System;
using System.Collections.Generic;
using System.Linq;

namespace tmp_cs
{
    class FlowerRange
    {
        int l, r;
        public FlowerRange(int left, int right)
        {
            l = left;
            r = right;
        }

        public int Left
        {
            get { return l; }
        }
        public int Right
        {
            get { return r; }
            set { r = value; }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            int n;
            //Dictionary contains ranges of flowers grouped and sorted by their moisture
            SortedDictionary<int, FlowerRange> Moisture_ranges = new SortedDictionary<int, FlowerRange>(); 
            //key - moisture of flower's group;
            //Range.Left, Range.Right - positions of leftest and rightest flowers with this moisture in flowerbed 
            n = Convert.ToInt32(Console.ReadLine());
            string[] m = Console.ReadLine().Split(' ');
            for (int i = 0; i < n; i++)
            {
                int moisture = Convert.ToInt32(m[i]);
                if (!Moisture_ranges.Keys.Contains(moisture))   //it's first flower with this moisture
                    Moisture_ranges.Add(moisture, new FlowerRange(i, i));
                else
                    Moisture_ranges[moisture].Right = i; //if range with this moisture already exists - we shift it's right border to new flower
            }

            //The shortest way to watering flowers according to problem is watering flowers starting from dryest, from left to right(or on the contrary)
            //in each moisture range, then moving to closest border(first or last) flower in next moisture range, and so on.
            long path_l = n, path_r = n;
            FlowerRange prev = new FlowerRange(0, 0);
            foreach (KeyValuePair<int, FlowerRange> moisture_range in Moisture_ranges)
            {
                //choose closest border of prev moisture_range for right border of current moisture_range
                long newpath_l = (Math.Abs(moisture_range.Value.Right - prev.Right) + path_r < Math.Abs(moisture_range.Value.Right - prev.Left) + path_l) ?
                            Math.Abs(moisture_range.Value.Right - prev.Right) + path_r : Math.Abs(moisture_range.Value.Right - prev.Left) + path_l;
                newpath_l += moisture_range.Value.Right - moisture_range.Value.Left;    //add distance from right to left flowers in current mois range

                //choose closest border of prev moisture_range for left border of current moisture_range
                long newpath_r = (Math.Abs(moisture_range.Value.Left - prev.Right) + path_r < Math.Abs(moisture_range.Value.Left - prev.Left) + path_l) ?
                            Math.Abs(moisture_range.Value.Left - prev.Right) + path_r : Math.Abs(moisture_range.Value.Left - prev.Left) + path_l;
                newpath_r += moisture_range.Value.Right - moisture_range.Value.Left;    //add distance from right to left flowers in current mois range
                path_l = newpath_l; //store shortest path ending at leftmost flower of current moisture_range flowers
                path_r = newpath_r; //store shortest path ending at rightmost flower of current moisture range flowers
                prev = moisture_range.Value;
            }
            Console.WriteLine((path_l < path_r) ? path_l : path_r); //choose shortest track

            return;
        }
    }
}