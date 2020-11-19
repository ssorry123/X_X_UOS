using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class ThreadState
    {
        public void ThreadBody()
        {
            while (true)
            {
            }
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            ThreadState obj = new ThreadState();    // 객체 생성
            ThreadStart ts = new ThreadStart(obj.ThreadBody);   // 델리게이트 연결
            Thread t = new Thread(ts);  // 스레드 객체 생성

            WriteLine("Step 1: " + t.ThreadState);  //Step 1: Unstarted
            t.Start();      // 해당 스레드를 실행한다
            Thread.Sleep(100);
            WriteLine("Step 2: " + t.ThreadState);  //Step 2: Running
            t.Suspend();    // 해당 스레드를 대기 상태로 만든다.
            Thread.Sleep(100);
            WriteLine("Step 3: " + t.ThreadState);  //Step 3: Suspended
            t.Resume();     // 대기 상태 스레드를 실행 상태로 만든다.
            Thread.Sleep(100);
            WriteLine("Step 4: " + t.ThreadState);  //Step 4: Running
            t.Abort();      // 해당 스레드를 종료시킨다.
            Thread.Sleep(100);
            WriteLine("Step 5: " + t.ThreadState);  //Step 5: Aborted
        }
    }
}
