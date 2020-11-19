using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class ThreadProperty
    {
        readonly object thisLock = new object();
        public void ThreadBody()
        {
            Thread myself = Thread.CurrentThread;
            Monitor.Enter(thisLock);
            for (int i = 1; i <= 3; i++)
            {
                WriteLine("{0} is activated => {1}", myself.Name, i);
                Thread.Sleep(1000);
            }
            Monitor.Exit(thisLock);
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            ThreadProperty obj = new ThreadProperty();
            ThreadStart ts = new ThreadStart(obj.ThreadBody);
            Thread t1 = new Thread(ts);
            Thread t2 = new Thread(ts);
            t1.Name = "Apple"; t2.Name = "Orange";
            t1.Start(); t2.Start();
        }
    }
}
