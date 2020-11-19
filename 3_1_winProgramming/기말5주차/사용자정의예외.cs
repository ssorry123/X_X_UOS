using System;
using static System.Console;

namespace ConsoleApp1
{// 사용자 정의 예외, 보통 ApplicationException을 상속받아 만듬.
    class UserErrException : ApplicationException
    {// 생성자에 예외에 관련된 메세지를 받을 수 있게 함.
        public UserErrException(string s) : base(s) { }
    }
    class App
    {
        static void Main(string[] args)
        {
            try
            {
                throw new UserErrException("throw a exception with a message");
            }
            catch (UserErrException e)
            {
                WriteLine(e.Message);
            }
        }
    }
}
