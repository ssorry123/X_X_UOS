using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class MyList : IEnumerable, IEnumerator
    {// 두 인터페이스를 상속해야함
        private int[] array;
        int position = -1; // 초기값은 첫번째인덱스보다 -1 이어야한다
        public MyList() { array = new int[3]; } // 초기 배열 크기는 3
        public int this[int index]
        {    //인덱서
            get { return array[index]; }
            set
            {
                if (index >= array.Length)
                { // 배열 크기를 넘어서 삽입하려하면
                    Array.Resize<int>(ref array, index + 1);
                    WriteLine($"Array Resized : {array.Length}");
                }
                array[index] = value;   // 삽입
            }
        }
        // IEnumerator 멤버들
        // 컬렉션의 현재 위치의 요소값을 반환한다
        public Object Current { get { return array[position]; } }
        // 다음 position으로 이동한다. 컬렉션의 끝을 지난 경우 false 리턴
        public bool MoveNext() {
            if (position == array.Length - 1) {
                Reset(); return false;
            }
            position++; // 따라서 초기값은 -1이 되어야 한다
            return (position < array.Length);   // 정상이동시 true 리턴
        }
        // 컬렉션의 첫번째 위치의 앞(-1)으로 이동한다
        public void Reset() {
            position = -1;
        }

        // IEnumerable 멤버
        public IEnumerator GetEnumerator() {
            for (int i = 0; i < array.Length; i++)
                yield return (array[i]);
                // 현재 함수를 종료시키지 않고 중지시킨후 값을 리턴한다
                // 재호출시 중지된 지점부터 return이나 break 만날때까지 실행
                // break는 종료시킨다
        }
    }
    class MainApp
    {
        static void Main(string[] args)
        {
            MyList list = new MyList();
            for (int i = 0; i < 5; i++)
                list[i] = i;
            foreach (int e in list)
                WriteLine(e);
        }
    }
}
