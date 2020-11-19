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
        {// 컴파일시 경고가 나타난다., 하지만 메소드는 호출할 수 있다.
            ObsoleteAttrApp.NormalMethod();
            ObsoleteAttrApp.OldMethod();
        }
    }
}
