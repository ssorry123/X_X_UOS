using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class BaseClass{
        public virtual void Output(){
            WriteLine("BaseClas");
        }
    }
    class DerivedClass : BaseClass{
        public override void Output(){  //객체 참조가 DerivedClass일때 호출
            WriteLine("Derived Clas");
        }
    }
    class Program
    {
        static void Print(BaseClass obj){ // 객체 형 BaseClass
            obj.Output();
        }
        public static void Main(string[] args)
        {
            BaseClass obj1 = new BaseClass();
            DerivedClass obj2 = new DerivedClass();
            Print(obj1);    // BaseClass obj = obj1(BaseClass) 
            Print(obj2);    // BaseClass obj = obj2(DerivedClass)
            obj1 = new DerivedClass();
            Print(obj1);
        }
    }
}
