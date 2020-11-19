using System;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class MainApp
    {
        static void Main(string[] args)
        {   // 람다식을 이용해 식트리 만들기
            Expression<Func<int, int, int>> expression =
                 (a, b) => 1 * 2 + (a - b);
            Func<int, int, int> func = expression.Compile();

            //x = 7, y = 8
            WriteLine("1*2 + ({0}-{1}) = {2}", 7, 8, func(7, 8));
        }
    }
}
