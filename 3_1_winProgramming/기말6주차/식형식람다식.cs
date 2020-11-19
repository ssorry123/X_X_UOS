using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class MainApp
    {
        delegate int Calculate(int a, int b);   // 델리게이트 생성
        delegate double Calculate1(double a, double b);
        static void Main(string[] args)
        {// 형식 유추 기능으로 매개변수를 컴파일러가 유추해준다.
            Calculate calc = (a, b) => a + b;   // 식 형식의 람다식
            WriteLine($"{3} + {4} : {calc(3, 4)}");
            Calculate1 calc1 = (a, b) => a + b;
            WriteLine($"{3} + {4} : {calc1(3.4, 4.7)}");
        }
    }
}
