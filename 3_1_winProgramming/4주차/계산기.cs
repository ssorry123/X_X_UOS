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
            int x, y, r = 0;
            string opr, xstr, ystr;
            Write("Enter an operator & two numbers = ");
            opr = ReadLine();
            xstr = ReadLine();
            ystr = ReadLine();
            x = int.Parse(xstr);
            y = int.Parse(ystr);
            switch (opr)
            {
                case "+":
                    r = x + y;
                    WriteLine(r);
                    WriteLine(r.ToString("000.00"));    // 형식을 포맷해줄 수 있음
                    break;
                default:break;
                case "-":
                    r = x - y;
                    WriteLine(r); break;
                case "*":
                    r = x * y;
                    WriteLine(r); break;
                case "/":
                    r = x / y;
                    WriteLine(r); break;
                case "%":
                    r = x / y;
                    WriteLine(r); break;
            }
        }
    }
}

