using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class MainApp
    {
        // 17개의 Func 델리게이트가 .NET 프레임 워크에 선언되어 있다.
        static void Main(string[] args)
        {
            Func<int> func1 = () => 10; // 매개변수 없이 무조건int 10 반환
            WriteLine(func1());
            Func<int, int> func2 = (x) => x * 2; // 매개변수는 int하나, 반환형 int
            WriteLine(func2(3));
            Func<int, int, int> func3 = (x, y) => x + y;
            WriteLine(func3(5, 7));
        }
    }
}
