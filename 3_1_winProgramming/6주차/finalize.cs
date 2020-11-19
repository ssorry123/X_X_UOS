using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class Test
    {
        public Test() { WriteLine("생성자"); }
        ~Test() { WriteLine("소멸자"); }
        //~Test()는 Finalize() 로 override되어 컴파일된다.
    }
    class Program
    {
        public static void Main(string[] args) {
            Test t = new Test();    //객체생성
            WriteLine("실행중"); 
            // 종료시 소멸자 실행
        }
    }
}
