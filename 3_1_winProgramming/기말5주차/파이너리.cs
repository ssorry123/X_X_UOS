using System;
using static System.Console;

namespace ConsoleApp1
{
    class App
    {
        static void Main(string[] args)
        {
            int i = 1;int j = 0;
            int k;
            for (; ; )
            {
                try { k = i / j; } // System이 Exception 객체를 던진 것이다.
                catch (Exception e) { WriteLine(e.Message); break; }
                finally { WriteLine("finally"); }
            }// break 후 finally 출력하고 빠져나옴.
        }
    }
}
