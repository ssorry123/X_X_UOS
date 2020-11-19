using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class ThreadJoin
    {// 주어진 수보다 큰 완전수(자신을 제외한 약수의 합과 같은 수)
        public int start;
        public int perfectNumber;
        public void ThreadBody()
        {
            int sum;
            for (int i = start; ; i++)
            {
                sum = 0;
                for (int j = 1; j <= i / 2; j++) // 약수는 1부터 절반까지 가능
                    if (i % j == 0) sum += j;
                if (i == sum)   // 약수들의 합과 i가 같으면
                {
                    perfectNumber = i;
                    break;
                }
            }
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            ThreadJoin obj = new ThreadJoin();  // 객체 생성
            ThreadStart ts = new ThreadStart(obj.ThreadBody);   // 델리게이트 연결
            Thread t = new Thread(ts);  // 스레드 객체 생성
            Write("Enter a number : ");
            obj.start = int.Parse(ReadLine());  // 숫자 입력 받음
            t.Start();  // 스레드 시작
            t.Join();// t가 끝날떄까지 메인쓰레드는 멈춰서 기다린다.
            WriteLine("The perfect number over {0} is {1}", obj.start, obj.perfectNumber);
        }
    }
}
