using System;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class MainApp
    {
        static void Main(string[] args)
        {
            Expression const1 = Expression.Constant(1); // 상수 노드 생성
            Expression param1 = Expression.Parameter(typeof(int), "x"); // 매개변수 x 노드 생성

            Expression exp = Expression.Add(const1, param1);    // 위 두 노드의 부모 노드 생성

            Expression<Func<int, int>> lambda1 =         // Expression<TDelegate> 클래스 이용
                Expression<Func<int, int>>.Lambda<Func<int, int>>(
                    exp,    // 식트리 Body, 루트노드
                    new ParameterExpression[] { (ParameterExpression)param1 }   // 매개변수 배열
                    );

            // Expression<TDelegate> 을 컴파일 하여 람다식 무명함수를 생성
            Func<int, int> compiledExp = lambda1.Compile();

            WriteLine(compiledExp(3));  // 1 + 3 => 4
        }
    }
}
