using System;
using static System.Console;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class MainApp
    {
        delegate string Concatenate(string[] args);
        static void Main(string[] args)
        {
            Concatenate concat = (arr) => {
                string result = "";
                foreach (string s in arr)
                    result += s;
                return result;
            };
            // args를 인자로 넘겨주어 실행
            WriteLine(concat(args));
        }
    }
}
