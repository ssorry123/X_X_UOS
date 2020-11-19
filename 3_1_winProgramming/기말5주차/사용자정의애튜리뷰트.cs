using System;
using static System.Console;

namespace ConsoleApp1
{
    public class MyAttr1Attribute : Attribute
    {// 사용자 정의는 Attribute를 상속한다.
        public MyAttr1Attribute(string message) { this.message = message; }
        private string message;
        public string Message { get { return message; } }
    }
    public class MyAttr2Attribute : Attribute
    {// 사용자 정의는 Attribute를 상속한다.
        public MyAttr2Attribute(string message) { this.message = message; }
        private string message;
        public string Message { get { return message; } }
    }
    [MyAttr1("This is Attribute test")]  // MyAttrAttribute에서 Attribute때고 사용
    [MyAttr2("Attribute 두개!")]
    class MyAttributeApp
    {// class MYAttributeApp 에 애튜리뷰트로 속성 정보 추가
        static void Main(string[] args)
        {
            Type type = typeof(MyAttributeApp);
            object[] arr1 = type.GetCustomAttributes(typeof(MyAttr1Attribute), true);
            object[] arr2 = type.GetCustomAttributes(typeof(MyAttr2Attribute), true);
            // MyAttrAttribute클래스의 속성정보를 .net프레임워크의 리플렉션 기능으로 속성정보 가져옴
            if (arr1.Length == 0) WriteLine("This class has no custom attrs");
            else{// arr1.Lenght == 1;
                MyAttr1Attribute ma = (MyAttr1Attribute)arr1[0];
                WriteLine(ma.Message);
            }
            if (arr2.Length == 0) WriteLine("This class has no custom attrs");
            else{// arr2.Lenght == 1;
                MyAttr2Attribute ma = (MyAttr2Attribute)arr2[0];
                WriteLine(ma.Message);
            }
        }
    }
}
