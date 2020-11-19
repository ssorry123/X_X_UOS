using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    // 추상클래스 정의
    abstract class AbstractClass
    {
        public abstract void MethodA();                     // 추상메소드, abstract virtual
        public void MethodB() { WriteLine("메쏟 B"); }      // 추상클래스에서 Body까지 정의
    }
    class ImpClass : AbstractClass
    {// new는 안되고override로 재정의 해야함..
        public override void MethodA() { WriteLine("메쏟 A"); }
        // MethodB 는 그대로 상속
    }
    // 추상메소드는 public이나 protected이어야 한다.
    class B { protected virtual void bbb() { } }
    class A : B
    {
        // virtual 메소드는 new나 override 둘다 가능.
        public new void bbb() { }
        //public override void bbb(){}
    }
    class Program
    {
        public static void Main(string[] args)
        {
            ImpClass obj = new ImpClass();
            obj.MethodA();
            obj.MethodB();
        }
    }
}
