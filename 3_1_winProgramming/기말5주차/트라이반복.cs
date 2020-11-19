using System;
using static System.Console;

namespace ConsoleApp1
{
    class App
    {
        static void Main(string[] args)
        {
            int count = 0;
            while (true)
            {
                try
                {
                    if (++count == 1) throw new Exception();
                    if (count == 3) break; // 빠져나가기 전에도 finally를 실행하고 빠져나간다.
                    WriteLine(count + ") No exception");
                }
                catch (Exception) { WriteLine(count + ") Exception Throw"); }
                finally { WriteLine(count + ") is finally "); }
            }
            WriteLine("Main program ends");
            //1) Exception Throw
            //1) is finally
            //2) No exception
            //2) is finally
            //3) is finally
            //Main program ends
        }
    }
}
