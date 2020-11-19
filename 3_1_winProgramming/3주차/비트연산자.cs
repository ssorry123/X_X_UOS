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
            WriteLine(10 << 2); //40, 10*2=20, 20*2=40
            WriteLine(10 >> 2); // 2, 10/2=5,   5/2=2 !!!!
            WriteLine(10 >> 1); // 5
        }
    }
}

