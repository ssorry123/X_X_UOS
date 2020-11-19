using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class StringApp { }
    class Program
    {
        static void Main(string[] args)
        {
            StringApp obj = new StringApp();
            //객체 생성
            string str = "Class name is";
            WriteLine(str + obj.ToString());
            //Class name is윈도우즈프로그래밍.StringApp
            StringBuilder sb = new StringBuilder();
            sb.Append(str);
            sb.Append(obj.ToString());
            WriteLine(sb);
            //Class name is윈도우즈프로그래밍.StringApp
        }
    }
}
