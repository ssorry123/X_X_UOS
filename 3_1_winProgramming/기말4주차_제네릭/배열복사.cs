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
        static void CopyArray<T>(T[] source, T[] target)
        {
            for (int i = 0; i < source.Length; i++)
                target[i] = source[i];
        }
        public static void Main(string[] args)
        {
            int[] source = { 1, 2, 3, 4, 5 };
            int[] target = new int[source.Length];
            CopyArray<int>(source, target); // 복사 실행
            foreach (int element in target) // 복사 확인
                WriteLine(element);
            string[] source2 = { "하나", "둘" };
            string[] target2 = new string[source2.Length];
            CopyArray<string>(source2, target2);
            foreach (string str in target2)
                WriteLine(str);
        }
    }
}
