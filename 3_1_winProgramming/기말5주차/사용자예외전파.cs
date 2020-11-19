using System;
using static System.Console;

namespace ConsoleApp1
{
    class these : ApplicationException { }
    class App
    {
        static void Method()
        {
            throw new these();
            // throw 밑부분은 실행되지 않는다. catch를 찾아야 한다.
            // 여기는 없으니 자신을 호출한 메소드를 찾아간다.
            // 만약 Main에도 catch가 없으면?
            // 사용자 정의 예외이므로 컴파일 에러가 발생한다.
        }
        static void Main(string[] args)
        {
            try
            {
                WriteLine("1");
                Method();
                WriteLine("2"); // 실행되지 않는다.
            }
            catch (Exception e)
            {
                WriteLine(e.Message);
            }
        }
    }
}