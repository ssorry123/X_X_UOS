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
        static void Main(string[] args)
        {//배열의 배열
            int[][] arrayofArray = new int[3][];
            int i, j;
            for (i = 0; i < arrayofArray.Length; i++)
                arrayofArray[i] = new int[i + 3];
            for (i = 0; i < arrayofArray.Length; i++)
                for (j = 0; j < arrayofArray[i].Length; j++)
                    arrayofArray[i][j] = i * arrayofArray[i].Length + j;
            for (i = 0; i < arrayofArray.Length; i++)
            {
                for (j = 0; j < arrayofArray[i].Length; j++)
                    Write("  " + arrayofArray[i][j]);
                WriteLine();
            }
        }
    }
}
