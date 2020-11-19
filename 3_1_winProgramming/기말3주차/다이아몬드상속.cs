using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    interface IX { void XMethod(int x); }
    interface IY : IX { void YMethod(int i); }  // 인터페이스가 인터페이스를 상속
    class A : IX
    {
        public int PropertyA { get; set; }
        public void XMethod(int i) { PropertyA = i; }   //IX의 XMethod구현
    }
    class B : A, IY
    {// A로부터 ProPertyA,XMethod(구현됨)상속, IY로부터 YMethod, Xmethod상속
        // Xmethod도 상속받았지만 A에서 구현해서 안해도 된다
        public int PropertyB { get; set; }
        public void YMethod(int i) { PropertyB = i; }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            B obj = new B();
            obj.XMethod(5);
            obj.YMethod(10);
            WriteLine("a = {0},  b = {1}", obj.PropertyA, obj.PropertyB);

        }
    }
}
