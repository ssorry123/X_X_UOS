using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{

    class Fraction
    {
        // int numerator;
        // int denominator;
        int[] array;

        // 자동 선언 프로퍼티, int numerator, denominator 선언없이도 사용가능..
        public int Numerator { get; set; }
        public int Denominator { get; set; }

        public Fraction(int size) { array = new int[size]; }  //생성자

        public int this[int i]
        {// 인덱서, get,set에서 내부필드 array와 인덱스도 가리킨다.
            get { return array[i]; }
            set { array[i] = value; }
        }
        public int[] Array
        {// 어레이 프로퍼티, array이름만 가리킨다.
            get { return array; }
            set { array = value; }
        }
        override public string ToString() { return String.Format(Numerator + "/" + Denominator); }
    }
    // 리드만 가능하거나 라이트만 가능한 프로퍼티를 만들 수 있따.,, get이나 set 둘중 하나만 선언.
    class Program
    {
        public static void Main(string[] args)
        {
            Fraction f = new Fraction(6); int i;
            f.Numerator = 1;
            i = f.Numerator + 1;
            f.Denominator = i;
            Console.WriteLine(f); //   1/2
            for (i = 0; i < f.Array.Length; i++)
            {    // 배열 프로퍼티에서 Length프로퍼티도 가능.
                f.Array[i] = i; //어레이프로퍼티는 객체.프로퍼티이름[index] 로 접근
                Write(f.Array[i] + " ");
            }WriteLine();
            for (i = 0; i < 6; i++)
            { // 인덱서에서는 Length 프로퍼티를 지원하지 않는다.
                f[i] = i; //인덱서는 객체.[index] 로 접근.
                Write(f[i] + " ");
            }

        }
    }
}
