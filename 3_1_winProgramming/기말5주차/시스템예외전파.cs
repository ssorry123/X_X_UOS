using System;
using static System.Console;

namespace ConsoleApp1
{
    class SystemExThrow
    {
        public static void Exp(int ptr)
        {
            if (ptr == 0)
                throw new NullReferenceException();
        }
    }
    class App
    {
        static void Main(string[] args)
        {
            int i = 0;
            try{SystemExThrow.Exp(i);}
            catch (NullReferenceException e) { WriteLine(e.Message); }
            int[] vector = { 1, 2, 3 };
            vector[4] = 4;// 이것은 default 처리기가 처리
        }

    }
}
