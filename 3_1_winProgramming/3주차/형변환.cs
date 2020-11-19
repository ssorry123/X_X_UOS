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
        static void Main(string[] args)
        {
            //0x7fff_ffff=0111_1111_1111_1111_1111_1111_1111_1111
            int i = 0xffff; //0000_0000_0000_0000_1111_1111_1111_1111
            // 16진수 한개 = 4bit, int 형은 32bit=4byte..
            short s;        //1111_1111_1111_1111   short형은 16bit=2byte..
            s = (short)i;   //short를 빼면 에러 발생, short가 int보다 작으므로
            WriteLine(i);
            WriteLine(s);   // 형변환을 하면 값이 달라진다. 비트가 모두 1이면 -1

            // 큰 int를 float한후 다시 int 하면 정확도가 떨어짐.
            int big = 1234567890;
            float approx;
            approx = (float)big;
            WriteLine(big - (int)approx);
        }
    }
}

