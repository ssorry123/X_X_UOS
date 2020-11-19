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
        static int ReadInt()
        {//대표적인 숫자읽기
            char ch;
            int n = 0;
            while (!char.IsDigit(ch = (char)Read()));
            // 버퍼에 숫자가 아닌 캐릭터가 나오면 계속 다시 읽는다.
            do
            {// 첫 문자는 숫자일것이므로
                n = n * 10 + (ch - '0');
                ch = (char)Read();  //다시 읽고

            } while (char.IsDigit(ch)); //계속 숫자가 나오면 읽는다.
            // 숫자가 아닌 것이 나오면 return한다.
            return n;
        }

        static void Main(string[] args)
        {
            //숫자가 스트링으로 묵시적 형변환 일어남
            WriteLine("***readdata : " + ReadInt() + " " + ReadInt());

            //
            double d = Math.PI;
            WriteLine("10)  " + d.ToString("0.0000"));  //형식 포맷하기
        }
    }
}
