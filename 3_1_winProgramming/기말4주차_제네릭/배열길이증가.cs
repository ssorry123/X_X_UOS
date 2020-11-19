using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class MyList<T>
    {
        private T[] array;  // T배열
        public MyList() { array = new T[3]; }   // 생성자, 기본크기 3
        public T this[int index]
        {  // 인덱서
            get { return array[index]; }
            set
            {
                if (index >= array.Length)
                {// array 배열의 사이즈 증가
                    Array.Resize<T>(ref array, index + 1);
                    WriteLine("{0}'s T[] array size = {1} + 1", this, index);
                }
                array[index] = value;
            }
        }
        public int Length { get { return array.Length; } }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            MyList<string> str_list = new MyList<string>();
            for (int i = 0; i < 4; i++)
                str_list[i] = "AB";
            MyList<int> int_list = new MyList<int>();
            for (int i = 0; i < 4; i++)
                int_list[i] = i;
        }
    }
}
