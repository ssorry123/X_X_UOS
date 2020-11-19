
#define CSHARP  // 명칭 있는 거만 실행됨
using System;
using static System.Console;
using System.Diagnostics;   // 추가해야됨.
namespace ConsoleApp1
{
    class ConditionalAttr {
        [Conditional("CSHARP")] // 조건부 애트리뷰트
        public static void CsharpMethod() { WriteLine("C#");}
        [Conditional("JAVA")]
        public static void JavaMetod() {WriteLine("JAVA");}
    }
    class Program
    {
        static void Main(string[] args)
        {
            ConditionalAttr.CsharpMethod();
            ConditionalAttr.JavaMetod();
        }
    }
}
