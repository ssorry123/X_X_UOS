using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class Mile
    {
        public double distance;
        public Mile(double distance) { this.distance = distance; }
        public static implicit operator Mile(Double d) { Mile m = new Mile(d); return m; }
        public static explicit operator Kilometer(Mile m) { return m.distance = 1.609; }
    }
    class Kilometer
    {
        public double distance;
        public Kilometer(double distance) { this.distance = distance; }
        public static implicit operator Kilometer(double d) { Kilometer k = new Kilometer(d); return k; }
        public static explicit operator Mile(Kilometer k) { return k.distance; }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            Kilometer k = new Kilometer(100.0); // 킬로 객체 생성
            Mile m; //
            //명시적 Mile캐스팅이 double을 반환한후 , 묵시적 Mile캐스팅이 double이용해서 객체생성후 m에 할당
            m = (Mile)k;
            WriteLine(k.distance + "  " + m.distance);  //100.0, 100.0

            m = 65.0;   // 묵시적 Mile캐스팅이 실행되어 m객체의 distance에 65.0삽입
            // 명시적 Kilo캐스팅이 double(1.609) 을 반환한후, 묵시적 Kilo 캐스팅이 double이용 객체생성후 k에 할당
            k = (Kilometer)m;
            WriteLine(m.distance + "   " + k.distance); // 1.609, 1.609
        }
    }
}
