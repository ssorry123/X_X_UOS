using System;
using static System.Console;

namespace ConsoleApp1
{
    class propagateApp
    {
        void Orange()
        {
            int i = 25, j = 0;
            i = i / j;  // 에러 발생. 캐치 없어서 상단 함수로
            WriteLine("End of Orange method");
        }
        void Apple()
        {
            Orange();// 여기 아래에도 캐치가 없어서 상단 함수로
            WriteLine("End of Apple method");
        }
        static void Main(string[] args)
        {
            propagateApp p = new propagateApp();
            try
            {
                p.Apple();// 여기 아래에는 캐치가 있어서 아래 캐치에서 처리.
            }
            catch (ArithmeticException)
            {
                WriteLine("ArithmeticException is processed");
            }
            WriteLine("End of Main");
            //ArithmeticException is processed
            //End of Main
        }
    }
}
