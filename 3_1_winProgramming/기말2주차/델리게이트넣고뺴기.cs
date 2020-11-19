using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    public delegate void MultiDelegate();

    class DelegateClass
    {
        public void MethodA(){WriteLine("Method A..........");}
        public void MethodB(){WriteLine("Method B..........");}
        public void MethodC(){WriteLine("Method C..........");}
    }
    class Program
    {
        public static void Main(string[] args)
        {
            DelegateClass obj = new DelegateClass();
            MultiDelegate dg1, dg2, dg3;
            dg1 = new MultiDelegate(obj.MethodA);
            dg2 = new MultiDelegate(obj.MethodB);
            dg3 = new MultiDelegate(obj.MethodA);

            dg1 = dg1 + dg2;
            dg2 -= dg3;

            dg1();  //dg1 = dg1 dg2 -dg3 -> A, B
            dg2(); // dg2 = dg2 - dg3    -> B
        }
    }
}
