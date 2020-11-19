using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    interface IVector
    {
        void Insert(int n);
        void ScalarSum(int n);
        void PrintVector();
    }
    struct Vector : IVector
    {
        private int[] v;
        private int index, size;

        public Vector(int size)
        {// 생성자
            v = new int[size]; this.size = size; index = 0;
        }
        public void Insert(int n)
        {
            if (index >= size) WriteLine("에러 어레이 오버플로우");
            else v[index++] = n;
        }
        public void ScalarSum(int n) { for (int i = 0; i < index; i++) v[i] += n; }
        public void PrintVector()
        {
            for (int i = 0; i < index; i++) Write("  " + v[i]);
            WriteLine();
        }
    }


    class Program
    {
        public static void Main(string[] args)
        {
            Vector a = new Vector(100);
            int n;
            while (true)
            {
                //n = Read() - '0';
                string str = ReadLine();    // 읽고
                n = int.Parse(str);
                if (n == 0) break;         // 0이면 종료
                a.Insert(n);                // 0아니면 삽입
            }
            a.PrintVector(); a.ScalarSum(10); a.PrintVector();

        }
    }
}

