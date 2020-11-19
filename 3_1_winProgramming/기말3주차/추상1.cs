using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class CL{
        virtual public void Print(){
            WriteLine("in the CL");
        }
    }
    class Java : CL{
        public override void Print(){
            WriteLine("in the java class");
        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            CL c = new CL();
            c.Print();  // in the CL
            c = new Java();
            c.Print();  // in the java

            Java j = new Java();
            j.Print();  // in the java
        }
    }
}

