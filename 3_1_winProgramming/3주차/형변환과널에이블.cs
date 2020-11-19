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
            int foo = 526; object bar = foo;   //int로 묵시적 boxing
            WriteLine(bar);
            try
            {
                double d = (int)bar;    //int가 아닌 것으로  unboxing 하면 에러
                WriteLine(d);
            }
            catch (InvalidCastException e) { WriteLine(e + "Errorrrrrrrrrr"); }

            double? num1 = null;
            double? num2 = 10.9;
            if (num1.HasValue) WriteLine(num1.Value);
            else WriteLine("null");

            if (num2.HasValue) WriteLine(num2.Value);
            else WriteLine("null");
        }
    }
}

