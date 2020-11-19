using System;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class MainApp
    {
        static void Main(string[] args)
        {   // 1*2 + (x-y)
            Expression const1 = Expression.Constant(1); // 상수 노드 1 생성
            Expression const2 = Expression.Constant(2); // 상수 노드 2 생성
            // 상수노드1과 상수노드2의 부모노드 생성
            Expression leftExp = Expression.Multiply(const1, const2);

            Expression param1 = Expression.Parameter(typeof(int));   // x 노드 생성
            Expression param2 = Expression.Parameter(typeof(int));   // y 노드 생성
            // x노드와 y노드의 부모노드 생성
            Expression rightExp = Expression.Subtract(param1, param2);

            Expression exp = Expression.Add(leftExp, rightExp); // 루트 노드 생성

            //람다식 클래스로
            Expression<Func<int, int, int>> expression =
                Expression<Func<int, int, int>>.Lambda<Func<int, int, int>>(
                    exp,
                    new ParameterExpression[]
                    {(ParameterExpression)param1, (ParameterExpression)param2}
                    );

            Func<int, int, int> func = expression.Compile();    // 무명함수로 컴파일
            WriteLine($"1*2+{7}-{8} = {func(7, 8)}");
        }
    }
}
