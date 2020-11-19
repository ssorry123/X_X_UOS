using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class StructArray<T> where T : struct
    {// T는 값형이어야 한다
        public T[] Array { get; set; }
        public StructArray(int size) { Array = new T[size]; }
    }
    class RefArray<T> where T : class
    {// T는 참조형이여야 한다
        public T[] Array { get; set; }
        public RefArray(int size) { Array = new T[size]; }
    }
    class Base { }
    class Derived : Base { }
    class BaseArray<U> where U : Base
    {// U는 Base로부터 파생된 클래스여야 한다.
        public U[] Array { get; set; }  // 어레이 프로퍼티
        public BaseArray(int size) { Array = new U[size]; } // 생성자
        // Array배열의 0번 인덱스부터부터 Target배열로 복사한다.
        public void CopyArray<T>(T[] Target) where T : U { Target.CopyTo(Array, 0); }
    }
    class NEWCLASS<T> {
        private int a;
        public NEWCLASS() { a = 1; }
        public NEWCLASS(int a) { this.a = a; }
    }
    class Program
    {
        public static T CreateInstance<T>() where T : new()
        {// T는 매개변수가 없는 생성자가 있어야 한다.
            return new T();
        }
        static void Main(string[] args)
        {
            StructArray<int> a = new StructArray<int>(3);   //T는 값형이여야 한다

            RefArray<StructArray<double>> b = new RefArray<StructArray<double>>(3);
            // T는 참조형이여야 한다, 값형을 제네릭으로 가지는 StructArray클래스
            b.Array[0] = new StructArray<double>(5);

            BaseArray<Base> c = new BaseArray<Base>(3);
            // Base제네릭에 자식 클래스를 넣을 수 있다.
            c.Array[0] = new Base();
            c.Array[1] = new Derived();
            c.Array[2] = CreateInstance<Base>();

            BaseArray<Derived> d = new BaseArray<Derived>(3);
            d.Array[0] = new Derived();
            d.Array[1] = CreateInstance<Derived>();
            d.Array[2] = CreateInstance<Derived>();
            // d.Array[3] = new Base(); 부모는 들어갈 수 없다

            BaseArray<Derived> e = new BaseArray<Derived>(3);
            e.CopyArray<Derived>(d.Array);
            BaseArray<Base> f = new BaseArray<Base>(3);
            f.CopyArray<Base>(c.Array);
            f.CopyArray<Derived>(d.Array);
        }
    }
}
