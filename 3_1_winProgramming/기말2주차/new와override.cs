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
        public virtual void MethodA()
        {   // new 재정의는 객체타입(형)를 따른다.
            WriteLine("in the BaseClass MethodA()");
        }
        public virtual void MethodB()
        {   // override 재정의는 객체참조를 따른다.
            WriteLine("in the BaseClass MethodB()");
        }
    }
    class DerivedClass : BaseClass
    {
        new public void MethodA()
        {   // new 재정의는 객체타입(형)를 따른다.
            WriteLine("in the DerivedClass... new override MethodA()");
        }
        override public void MethodB()
        {   // override 재정의는 객체참조를 따른다.
            WriteLine("in the DerivedClass... override override MethodB()");
        }
        public void MethodA(int i)
        {   // Base의 MethodA 와 시그니쳐가 다르므로 새롭게 정의된 메쏘드A라 할 수 있다.
            WriteLine("in the DerivedClass,,  overloading!!!! MethodA(int i)");
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {   // new 왼쪽은 객체 형(타입), override 오른쪽은 객체 참조.
            BaseClass obj1 = new BaseClass();
            BaseClass obj2 = new DerivedClass();    // Base가 더큰 클래스 타입이므로 DerivedClass 객체 참조 할당 가능
            DerivedClass obj3 = new DerivedClass();
            // DerivedClass obj4 = new BaseClass(); // 작은 클래스타입에 큰 클래스 객체 참조 할당 불가

            obj1.MethodA();     // new이므로 객체 형인 Base의 메소드 호출
            obj1.MethodB();     // override이므로 객체참조인 Base 메소드 호출

            obj2.MethodA();     // new이므로 객체형인 Base의 메소드 호출
            obj2.MethodB();     // override이므로 객체참조인 Derived 메소드 호출

            obj3.MethodA();     // new이므로 객체형인 Derived의 메소드 호출
            obj3.MethodB();     // override이므로 객체참조인 Derived 메소드 호출
        }
    }
}
