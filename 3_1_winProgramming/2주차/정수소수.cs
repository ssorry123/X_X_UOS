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
            int i; double x;
            i = 1 / 2;  //0     .이 있으면 기본은 double
            x = 1 / 2;  //0     .이 없으면 기본은 int
            // 0 이 double로 바껴서 들어간다.
            Write("i = " + i);
            WriteLine(",  x = " + x);
            i = (int)(1 / 2.0); //0.5->0
            //(int)(double)
            x = 1 / 2.0;    //0.5
            // 묵시적 형변환
            Write("i = " + i);
            WriteLine(",  x = " + x);
        }
    }
}
