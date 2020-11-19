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
        static void Swap<DataType>(ref DataType x, ref DataType y)
        {
            DataType temp;
            temp = x; x = y; y = temp;
        }
        public static void Main(string[] args)
        {
            int a = 1, b = 2; double c = 1.5, d = 2.5;
            WriteLine("before a : {0}, b : {1}", a, b); Swap<int>(ref a, ref b);
            WriteLine("after  a : {0}, b : {1}", a, b);
            WriteLine("before c : {0}, d : {1}", c, d); Swap<double>(ref c, ref d);
            WriteLine("after  c : {0}, d : {1}", c, d);
        }
    }
}
