using System;
using static System.Console;

namespace ConsoleApp1
{
    class these1 : ApplicationException { }
    class these2 : ApplicationException { }

    class App
    {
        static void Method(int i)
        {
            if (i == 1) throw new these1();
            else throw new these2();
        }
        static void Main(string[] args)
        {
            try
            {
                WriteLine("Here: 1");
                Method(2);  // these2 에러 유발
                WriteLine("Here: 2");
            }
            catch (these1 e)
            {
                WriteLine("Exception these 1");
            }
            catch (these2 e)
            {// 프린트 후 에러 유발 해도 디폴트가 처리하지 않는다.
                WriteLine("Exception these 2");
                 throw new these1();
                // 밑으로 catch가 없고 시스템 정의가 아니기 때문에 컴파일 에러
            }
            WriteLine("Here: 3");

        }

    }
}
