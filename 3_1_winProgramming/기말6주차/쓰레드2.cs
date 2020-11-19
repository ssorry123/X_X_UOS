using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class ThreadProperty
    {
        public void ThreadBody()
        {
            Thread myself = Thread.CurrentThread; // 현재 실행중인 스레드 가져옴
            for (int i = 1; i <= 3; i++)
            {
                WriteLine("{0} is activated => {1}", myself.Name, i);
                Thread.Sleep(1000);
            }
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            ThreadProperty obj = new ThreadProperty();  // 객체 생성
            ThreadStart ts = new ThreadStart(obj.ThreadBody);   // 델리게이트 연결
            Thread t1 = new Thread(ts); // 객체 t1 생성
            Thread t2 = new Thread(ts); // 객체 t2 생성
            t1.Name = "Apple"; t2.Name = "Orange";  // 이름 설정
            t1.Start(); t2.Start(); // 실행
        }
    }
}
