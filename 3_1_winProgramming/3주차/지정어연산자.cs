using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace 윈도우즈프로그래밍
{
    class Apple
    {
        public int nSeeds = 0;
        public void Ripen() { /*...*/ }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Type t = typeof(Apple);     //Apple클래스의 객체형반환
            string className = t.ToString();    //을 스트링으로 변환
            MemberInfo[] allMembers = t.GetMembers();   //t의 멤버들을 배열에 저장
            WriteLine(className + "  's Members:");
            foreach (MemberInfo member in allMembers)   //배열의 원소들(member)을 출력.
                WriteLine(member.ToString());
        }
    }
}

