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
            char c = 'A';
            int i;
            i = c + 1;  //묵시적 형변환

            WriteLine("{0},  {1}", c, (char)i);
            WriteLine("\"i am a string\"");// "i am a string"
            WriteLine(@"""i'm a string""");// "i'm a string"
        }
    }
}
