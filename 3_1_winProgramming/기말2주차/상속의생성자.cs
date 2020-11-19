using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class BaseClass
    {
        protected int a;    // 자기 클래스와 파생 클래스만 사용 가능.
        protected int b;

        public BaseClass() { a = 1; b = 2; }   //default 생성자
        public BaseClass(int a, int b) { this.a = a; this.b = b; }  //생성자 오버로딩
    }
    class DerivedClass : BaseClass
    {
        // a는 선언하지 않았으므로 상속받아 사용
        new double b = 4.8953; // 타입이 달라도 필드 재정의 가능
        public int c;

        public DerivedClass() { c = 3; }  // 기본 생성자
        public DerivedClass(int a, int b, int c) : base(a, b)   // 생성자 오버로딩
        {
            this.c = c;
        }
        public void Output()
        {
            WriteLine(base.a + "  " + a);
            WriteLine(base.b + "  " + b);
            WriteLine("   "+c);
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            DerivedClass obj = new DerivedClass();  //base만 호출
            obj.Output();   // 1,2  // 1,  4.8953,  3

            DerivedClass obj1 = new DerivedClass(5,6,7); // 오버로딩 생성자들 호출
            obj1.Output();  // 5, 6  // 5, 4.8953, 7
        }
    }
}
