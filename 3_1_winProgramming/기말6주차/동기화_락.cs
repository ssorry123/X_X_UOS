using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class ThreadProperty
    {
        object thisLock = new object();
        public void ThreadBody()
        {
            Thread myself = Thread.CurrentThread;
            // lock(this); 이것 보다 thisLock을 쓰는 것이 좋다
            lock (thisLock) // 이 {} 안은 원자적으로 실행된다.
            {
                for (int i = 1; i <= 3; i++)
                {
                    WriteLine("{0} is activated => {1}", myself.Name, i);
                    Thread.Sleep(1000);
                }
            }
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            ThreadProperty obj = new ThreadProperty();  // 객체 생성
            ThreadStart ts = new ThreadStart(obj.ThreadBody);   // 델리게이트 연결
            Thread t1 = new Thread(ts); // 스레드 객체 t1생성
            Thread t2 = new Thread(ts); // 스레드 객체 t2생성
            t1.Name = "Apple"; t2.Name = "Orange";  //이름 설정
            t1.Start(); t2.Start(); // 스레드 실행
        }
    }
}
