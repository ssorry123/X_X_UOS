using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    struct Point
    {
        //public int x=1, y;
        int x, y;    // 구조체에서 인스턴스 필드는 초기화값을 가질 수 없다.
        static int z = 3;    // static 필드는 초기화 값 가질 수 있음.
        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
        public override string ToString() { return "(" + x + "." + y + ")"; }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            Point[] pts = new Point[3]; // 구조체 객체 생성
            pts[0] = new Point(100, 100); pts[1] = new Point(100, 200); pts[2] = new Point(200, 100);

            foreach (Point pt in pts)
                WriteLine(pt.ToString());

            Point a = new Point(300, 300);
            Point b = a; // 똑같은 것을 가리키는 것이 아니라 내용이 모두 똑같이 복사된 후 b가 가리킴.
        }
    }
}
