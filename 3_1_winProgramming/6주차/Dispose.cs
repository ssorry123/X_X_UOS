using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class Test : IDisposable
    {// IDisposable 인터페이스를 구현한 Dispose함수가 있어야 한다.
        //....
        public void Dispose()
        {
            WriteLine("Dispose method running");
            GC.SuppressFinalize(this);
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            using (Test obj = new Test())
            {// 인터페이스를 하지 않으면 괄호 안에가 오류가 남.
                //...
            }
            WriteLine("End of Main");
        }
    }
}
