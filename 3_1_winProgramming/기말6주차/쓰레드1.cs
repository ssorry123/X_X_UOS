using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class SimpleThreadApp
    {
        public static void ThreadBody()
        {
            for (int i = 0; i < 5; i++)
            {
                WriteLine(DateTime.Now.Second + " . " + i);
                Thread.Sleep(1000); // 1초간 쉰다.
            }
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {// 델리게이트 연결후 쓰레드 객체 생성
            ThreadStart ts = new ThreadStart(SimpleThreadApp.ThreadBody);
            Thread t = new Thread(ts);
            WriteLine("***Start of Main");
            t.Start();
            WriteLine("*** End  of Main");
        }
    }
}
