using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class BaseClass {
         public virtual void MethodA() {
            WriteLine("Base");
        }
    }
    class DerivedClass : BaseClass
    {
        new public void MethodA() {
            base.MethodA();
            WriteLine("Derived");
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            DerivedClass d = new DerivedClass();
            d.MethodA();
        }
    }
}
