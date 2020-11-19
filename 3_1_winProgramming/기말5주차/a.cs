#define CSHARP  // 명칭 있는 거만 실행됨
using System;
using static System.Console;
namespace ConsoleApp1
{
    class ObsoleteAttrApp
    {
        [Obsolete("경고, Obsolete")]
        public static void OldMethod() { WriteLine("OLD"); }
        public static void NormalMethod() { WriteLine("NORMAL"); }
    }
    class Program
    {
        static void Main(string[] args)
        {
            ObsoleteAttrApp.NormalMethod();
            ObsoleteAttrApp.OldMethod();
        }
    }
}
