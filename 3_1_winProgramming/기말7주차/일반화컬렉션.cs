using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class MainApp
    {
        static void Main(string[] args)
        {
            // 세가지 제네렉 컬렉션 모두 foreach 가능
            // 즉 IEnumerable 과 IEnumerator을 상속하고 있다
            List<int> list = new List<int>();
            list.Add(1);list.Add(2);list.Add(3);
            foreach (int element in list)
                WriteLine(element);     // 1 2 3
            for (int i = 0; i < list.Count; i++)
                WriteLine(list[i]);     // 1 2 3

            // 제네렉 컬렉션 큐와 스택은 인덱스로 접근 불가
            Queue<int> que = new Queue<int>();
            que.Enqueue(1);que.Enqueue(2);que.Enqueue(3);
            foreach (int element in que)
                WriteLine(element);     // 1 2 3
            //for (int i = 0; i < que.Count; i++)
            //    WriteLine(que[i]);

            Stack<int> stk = new Stack<int>();
            stk.Push(1);stk.Push(2);stk.Push(3);
            foreach (int element in stk)
                WriteLine(element);     // 3 2 1 !!!!
            //for (int i = 0; i < stk.Count; i++)
            //    WriteLine(stk[i]);
        }
    }
}
