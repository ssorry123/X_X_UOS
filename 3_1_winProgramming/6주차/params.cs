using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{

    class Program
    {
        static void ParameterArray(params object[] obj) {
            int i;
            for (i = 0; i < obj.Length; i++)
                Write("{0}\t",obj[i]);WriteLine();
            foreach (object ooo in obj)
                Write("{0}\t",ooo);WriteLine();
        }
        static void Main(string[] args)
        {
            ParameterArray(123,"ABC",false,true,'C',3.14);
        }
    }
}
