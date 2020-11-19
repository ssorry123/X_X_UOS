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
            char a; int i;
            // i = Int32.Parse(ReadLine()); //숫자(유니코드값)입력받음
            //  a = (char)i;    //캐릭터형으로변환
            //  WriteLine(a);   //캐릭터출력
            //  WriteLine(i);   //숫자출력


            Boolean print = false;
            bool x;
            for (i = 0; i < 65536; i++)
            {
                if ((char)i == '가')
                    print = true;
                if (print)
                    Write("{0,5} {1:x}", (char)i, i);
                if ((char)i == '힣')
                    print = false;
            }

        }
    }
}
