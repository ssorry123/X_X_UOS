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
            Int32 i, max = int.MaxValue;
            try
            {
                WriteLine("try문 시작");
                i = max + 1;
                WriteLine("1i  =  " + i);
                WriteLine("체크 디폴트일때");
                unchecked
                {
                    i = max + 1;
                    WriteLine("2i  =  " + i);
                }
                WriteLine("체크 unchecked일때");
                checked
                {
                    i = max + 1;
                    WriteLine("3i  =  " + i);
                }
                WriteLine("체크 checked일때");


            }
            catch (Exception e) { WriteLine("오버플로우 예외를 잡았따." + e); }

            WriteLine("asdfasdfsdaf");
            string s = "1234567";
            long a = Int64.Parse(s);
        }
    }
}

