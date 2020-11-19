using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class CL
    {
        // obj 는 참조나 값형 모두 받아버릴수 있따
        public bool Equal(object obj)
        {   //obj가 CL타입으로 변환 가능한가?
            if (obj is CL) return true;
            else return false;
        }
    }
    class CS : CL
    {   // obj가 CS 타입으로  변환 가능한가?
        new public bool Equal(object obj) { return (obj is CS) ? true : false; }
    }
    class Program
    {
        public static void Main(string[] args)
        {   // CL이 CS보다 높음, 부모임, 더큼
            CL cl = new CL();
            CS cs = new CS();
            // cs는 cl보다 작으므로 cl로 자동 형변환 가능(), 상위클래스타입으로 캐스팅 가능
            if (cl.Equal(cs)) { WriteLine("casting up vaild"); }
            else WriteLine("casting up is not vaild");
            // cl이 cs보다 크므로 cl이 cs로 자동형변환 될 수 없음, 하위클래스타입으로 캐스팅 불가능
            if (cs.Equal(cl)) { WriteLine("casting down is vaild"); }
            else WriteLine("casting down is not vaild");
        }
    }
}
