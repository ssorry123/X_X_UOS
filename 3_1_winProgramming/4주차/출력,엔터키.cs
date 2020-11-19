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
            int n, s, i;
            Write("Enter a number = ");
            for (; ; )
            {
                n = Read() - '0';   //한자리!숫자를 입력받음
                if (n == 0) break;
                else if (n < 0) { WriteLine("-----"); continue; }
                //enter를 치면 음수로 입력됨.
                for (s = 0, i = 1; i <= n; i++)
                    s += i;
                WriteLine("n = {0}, s = {1,-5:X}", n, s);
            }
            WriteLine("End of Main");
            double d = Math.PI;
            WriteLine("{0,1:e}", d);
        }
    }
}
