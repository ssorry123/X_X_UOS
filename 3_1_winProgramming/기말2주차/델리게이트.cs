using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    public delegate void MultiDelegate();

    class Sch
    {
        public void Now()
        {
            WriteLine("Now   {0}", DateTime.Now.ToString());
        }
        public static void Today()
        {
            WriteLine("Today {0}", DateTime.Today.ToString());

        }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            Sch obj = new Sch();
            // 델리게이트에 객체형이나 static형 메소드 모두 형태만 같으면 연결 가능.
            MultiDelegate md = new MultiDelegate(obj.Now);
            md += new MultiDelegate(Sch.Today);
            md();   // now(), today()
        }
    }
}
