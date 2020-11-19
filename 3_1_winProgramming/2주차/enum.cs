using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{ 
    enum Color { Red, Green, Blue };
    enum AA { a = 5, b, c = 3 };
    class Program
    {
        static void Main(string[] args)
        {
            Color color = Color.Red;
            color++;    // Red->Green
            int colorI = (int)color;    //1
            //int로 형변환해주지 않으면 오류 발생
            WriteLine("{0}, {1}", color, colorI);
            // Green, 1
        }
    }
}

