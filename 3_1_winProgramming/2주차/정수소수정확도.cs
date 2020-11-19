using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{ 
    enum Color { Red, Green, Blue };
    enum AA { a = 5, b, c = 3 };
    class Program
    {
        static void Main(string[] args)
        {
            int a = 1000_0000;
            WriteLine(a * a);//276447232
            long b = a;
            WriteLine(b * b);//100000000000000

            double d = 0d;
            decimal m = 0m;
            for (int k = 0; k < 1000; k++)
            {//0.1을 1000번 더한다.
                d += 0.10d;
                m += 0.10m;
            }   // 0.1*1000
            WriteLine(d);WriteLine(m);
            //99.9999999999986, 100.00
        }
    }
}

