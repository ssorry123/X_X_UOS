using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class A
    {
        public static void method() { WriteLine("method()"); }
        public static void method(double a) { WriteLine("method(double)"); }
        public A() { WriteLine("public A()"); }
        public A(double d) { WriteLine("A(double)"); }
    }
    class Program
    {
        static void function(out int a) {
            a = 10;
        }
        static void Main(string[] args)
        {
            A.method(3);
            A a = new A(3);
  
            int x;
            function(out x);
        }
    }
}

