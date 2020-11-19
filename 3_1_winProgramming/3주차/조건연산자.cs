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
            int i, n = 25;//좋은 코드는 아니다.
            for (i = 1; i <= n; ++i)
                Write(i + ((i % 10 == 0 || i == n) ? "\n" : " "));
            // 10의 배수이거나 n 이면 \n, s나머지는 스페이스
            //1 2 3 4 5 6 7 8 9 10
            //11 12 13 14 15 16 17 18 19 20
            //21 22 23 24 25
        }
    }
}

