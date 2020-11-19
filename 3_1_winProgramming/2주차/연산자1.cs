using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class Program
    {
        static void Main(string[] args)
        {
            int x = 3, y = 5, z = 7;
            bool b1, b2;
            b1 = x > y; //false
            b2 = x < y && y < z;    // true && true
            WriteLine(b1 + "  " + b2);  //false, true
            b1 = x <= y;    //true
            b2 = (x >= y) == (y >= x);  // false == true
            WriteLine(b1 + "  " + b2);  // true, false
        }
    }
}
