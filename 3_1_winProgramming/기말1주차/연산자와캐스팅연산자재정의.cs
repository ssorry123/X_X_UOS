using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class XBool
    {
        public bool b;
        //explict, implict, 캐스팅연산자 bool 재정의/둘다 정의할수 없다.
        //public static implicit operator bool(XBool x){ WriteLine("implict bool"); return x.b;}
        public static explicit operator bool(XBool x) { WriteLine("implict bool"); return x.b; } 
        // true 연산자 재정의
        public static bool operator true(XBool x){ WriteLine("operator true"); return x.b ? true : false;}
        // false연산자 재정의
        public static bool operator false(XBool x){ WriteLine("operator false"); return x.b ? false : true; }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            // (bool) 이라고 명시적 형변환 했을떄랑 안했을 때랑 차이가 있다.
            XBool xb = new XBool();
            xb.b = false;

            // implicit bool 이어도 명시적호출하면 implict bool이 호출됨.
            // implicit, explicit 둘다 없으면 캐스팅 연산자 (bool)을 사용할 수 없다.
            if ((bool)xb) WriteLine("TTTTTTTRue"); else WriteLine("FFFFFFFAlse");

            // implicit bool 이면 implicit bool 캐스팅연산자가 실행된다.
            // explicit bool 이면, 또는 캐스팅연산자재정의가 없으면 true, false 연산자 재정의가 실행된다.
            if (xb) WriteLine("TTTTTTTRue"); else WriteLine("FFFFFFFAlse");
            // 근데 false연산자 재정의는 어떻게 실행하지..??
        }
    }
}
