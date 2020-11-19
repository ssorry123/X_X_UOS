using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class MainApp
    {
        // 17개의 Action 델리게이트가 .NET 프레임 워크에 선언되어 있다.
        static void Main(string[] args)
        {
            Action act1 = () => WriteLine("Action()");
            act1();
            int result = 0;
            Action<int> act2 = (x) => result = x * x;
            act2(3); // result에 값을 저장. 반환은 없다.
            WriteLine(result);
            Action<double, double> act3 = (x, y) => 
            {
                double pi = x / y;
                WriteLine("Action<T1, T2>({0}, {1}) : {2}", x, y, pi);
            };
            act3(22.6, 7.1);
        }
    }
}
