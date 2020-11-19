using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{   // 중요, 시험에 반드시 나옴.
    public delegate int Compare(int a, int b);
    class Program
    {
        static void BubbleSort(int[] DataSet, Compare Comparer)
        {   // 배열참조와 델리게이트메소드(여기선 익명메소드)를 전달받는다.
            int i = 0; int j = 0; int temp = 0;
            for (i = 0; i < DataSet.Length - 1; i++)    // 0 ~ n-2번째까지
                for (j = 0; j < DataSet.Length - (i + 1); j++)  // i개씩 범위 감소
                    if (Comparer(DataSet[j], DataSet[j + 1]) > 0)
                    {   // j번째가 더 큰경우(오름차순) j+1번째와 SWAP한다.
                        temp = DataSet[j + 1];
                        DataSet[j + 1] = DataSet[j];
                        DataSet[j] = temp;
                    }
        }

        public static void Main(string[] args)
        {
            int[] array = { 113, 23, 27, 1452, 56 };
            BubbleSort(array, delegate (int a, int b) // 이 자리에서 함수를 정의, 익명 메소드, 재사용은 못한다.
             {
                 if (a > b) return 1;
                 else if (a == b) return 0;
                 else return -1;
             }
            );
            int[] array2 = { 123, 4, 125, 6, 4137, 15, 32 }; // 내림차순 정렬.
            BubbleSort(array2, delegate (int a, int b) { if (a < b) return 1; else if (a == b) return 0; else return -1;});
        }
    }
}

