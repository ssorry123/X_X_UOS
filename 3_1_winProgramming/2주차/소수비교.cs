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
            float f1 = 1.414f, f2 = 0.1414e01f;//1.414
            double d = 0.1414e1;    //1.414
            WriteLine("{0}  {1}  {2}", f1, f2, d);
            if (f1 == f2) WriteLine("yes"); //yes
            else WriteLine("NO");
            if (d == f1) WriteLine("yes");
            else WriteLine("NO");   //NO
        }
    }
}
