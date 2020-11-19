using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static void ThreadBody()
        {
            Thread.Sleep(1000);
        }
        public static void Main(string[] args)
        {// 스레드 델리게이트 생성후 스레드 객체 생성
            Thread t = new Thread(new ThreadStart(ThreadBody));
            t.Start(); // 스레드 시작
            WriteLine("Current Priority : " + t.Priority); //Normal
            ++t.Priority;   // ++연산자로 우선순위 증가
            WriteLine("Higher Priority : " + t.Priority); //AboveNormal
        }
    }
}
