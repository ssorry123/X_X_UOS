using System;
using static System.Console;

namespace ConsoleApp1
{
    class MyException : ApplicationException
    { // 반드시 상속
        public int value;
        public MyException() { }
        public MyException(string msg, int i) : base(msg)
        {// Message와 i를 정보로 받을 수 있음
            value = i;
        }
    }
    class App
    {
        static void F(int k)
        {
            if (k < 70 || k > 100)
                throw new MyException();
        }
        static void G(int k)
        {//  정보도 같이 전달하는 예외 생성
            if (k > 200)
                throw new MyException("Too Many", k);
            if (k < 50)
                throw new MyException("Too less", k);
        }
        static void Main(string[] args)
        {
            try {F(50);}
            catch (MyException e){WriteLine(e.StackTrace);}
            WriteLine("G");
            try{G(250);}
            catch (MyException e) {
                WriteLine(e.Message);       // 이미 존재하는 프로퍼티
                WriteLine(e.StackTrace);    // 이미 존재하는 프로퍼티
                WriteLine("This value is {0}", e.value);
            }
        //위치: ConsoleApp1.App.F(Int32 k) 파일 C:\Users\26060\Source\Repos\윈프\기말5주차\예외정보.cs:줄 20
        //위치: ConsoleApp1.App.Main(String[] args) 파일 C:\Users\26060\Source\Repos\윈프\기말5주차\예외정보.cs:줄 31
        //G
        //Too Many
        //위치: ConsoleApp1.App.G(Int32 k) 파일 C:\Users\26060\Source\Repos\윈프\기말5주차\예외정보.cs:줄 25
        //위치: ConsoleApp1.App.Main(String[] args) 파일 C:\Users\26060\Source\Repos\윈프\기말5주차\예외정보.cs:줄 34
        //This value is 250
        }
    }
}

