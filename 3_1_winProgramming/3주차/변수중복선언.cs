using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class Program
    {
        static int x;
        static void Main(string[] args)
        {
            int x = 1;
            {
                // c에서 가능하지만
                // 한 메소드 안에서 블록이 다르더라도 같은 이름의 변수를 선언할 수 없다.
                //int x; 불가
                int y = 2;
                WriteLine(x + "  " + y);
            }
            {
                int y = 3;  // 가능, 위 블록으 y는 소멸되므로
                WriteLine(x + "  " + y);
            }
            // 하지만 메소드 밖에서는 같은 이름도 선언 가능함.
            WriteLine(x);           //메소드 내의 x
            WriteLine(Program.x);   //클래스변수 x
        }
    }
}

