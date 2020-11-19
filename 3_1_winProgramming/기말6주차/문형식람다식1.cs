using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class MainApp
    {
        delegate void DoSomething();
        // 식 형식의 람다식으로는 반환형식이 없는 무명함수를 만들 수 없지만
        // 문형식의 람다식을 이용하면 가능하다.
        static void Main(string[] args)
        {// 매개 변수도 없고 반환 형식도 없다
            DoSomething Doit = () =>
            {
                WriteLine("뭔가를 출력해보자 이렇게!");
            };
            Doit();
        }
    }
}
