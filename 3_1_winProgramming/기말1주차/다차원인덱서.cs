using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    class StringIndexer
    {
        //이것(인덱서)은 메소드다. 필드를 접근하는게아니라 연산을 정의.
        public char this[string str, int index]
        {// str의 index번째 char를 반환
            get { return str[index]; }
        }
        // 메소드 오버로딩 == 이름은 같고 원소들은다르다., 반환형은 시그니쳐가아니다.
        public string this[string str, int index, int len]
        {// index부터 len만큼 짜른 string을 반환
            get { return str.Substring(index, len); }
        }
    }

    class Program
    {
        public static void Main(string[] args)
        {
            string str = "Hello";
            StringIndexer s = new StringIndexer();
            for (int i = 0; i < str.Length; i++)
                WriteLine("{0}[{1}] = {2}", str, i, s[str, i]);
            WriteLine("{0},,,{1}", str, s[str, 2, 3]);

        }
    }
}
