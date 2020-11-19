using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    interface IRectangle { void Area(int width, int height = 20); }
    interface ITriangle { void Area(int width, int height); }
    class Shape : IRectangle, ITriangle
    {// 클래스이름.메소드이름() 으로 구현하는 경우 public을 명시하면 안된다.
        void IRectangle.Area(int width, int height) { WriteLine("Rectangle are : {0}", width * height); }
        void ITriangle.Area(int width, int height) { WriteLine("Triangle are : {0}", width * height / 2); }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            Shape s = new Shape();
            // s.Area(20,20); 애매모호하기도하고 인터페이스.메소드로 구현한경우
            // s.Area(20,20); 으로 호출할 수 없다. 캐스팅 후 호출해야함.
            // s.IRectangle.Area(20,20);    s.으로 호출해야 한다.
            // s.ITriangle.Area(20,20);     s.으로 호출해야 한다.
            ((IRectangle)s).Area(20);
            ((ITriangle)s).Area(20, 20);
            IRectangle r = s;   // 인터페이스가 상위이므로 묵시적 캐스팅 가능
            ITriangle t = s;    // 캐스팅 업, 상향 캐스팅
            r.Area(30, 30);
            t.Area(30, 30);
        }
    }
}
