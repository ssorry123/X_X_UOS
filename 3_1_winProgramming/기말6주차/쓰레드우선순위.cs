using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static int interval;
        static void ThreadBody()
        {
            Thread myself = Thread.CurrentThread;   // 현재 실행중인 스레드를 가져옴
            WriteLine("Starting Thread : " + myself.Name);
            for (int i = 1; i <= 3 * interval; i++)
                if (i % interval == 0)  // 간격 마다 스레드의 이름을 출력
                    WriteLine(myself.Name + " : " + i);
            WriteLine("EndingThread : " + myself.Name);

        }
        public static void Main(string[] args)
        {
            Write("interval value : ");
            interval = int.Parse(ReadLine());   // interval 입력받음
            Thread.CurrentThread.Name = "MainThread";   // 메인 스레드 이름 설정
            //Thread.CurrentThread.Priority = ThreadPriority.Highest;
            Thread worker = new Thread(new ThreadStart(ThreadBody)); // 스레드 객체 생성
            worker.Name = "Worker Thread"; // 생성된 스레드 객체이름 설정 
            WriteLine("worker Priority : {0}, Main Priority :{1} ", worker.Priority, Thread.CurrentThread.Priority);
            // interval이 작으면 두개의 스레드가 병행처리 되지 않은 것처럼 보임
            // interval의 값을 크게 입력할 경우 두 개의 스레드가 병렬로 처리되는 것을 확인
            worker.Start();
            ThreadBody();
        }
    }
}
