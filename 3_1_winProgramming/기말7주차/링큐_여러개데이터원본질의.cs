using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class Class
    {
        public string Name { get; set; }
        public int[] Score { get; set; }    // 배열!
    }
    class MainApp
    {
        static void Main(string[] args)
        {
            Class[] arrClass =
            {//어레이 안에 또 어레이가 있다
                new Class(){ Name="연두반", Score = new int[]{ 99,80,70,24} },
                new Class(){ Name="분홍반", Score = new int[]{ 60,45,87,72} },
                new Class(){ Name="파랑반", Score = new int[]{ 92,30,85,94} },
                new Class(){ Name="노랑반", Score = new int[]{ 90,88,0,17} },
            };
            var classes = from c in arrClass    // 범위 변수 c(객체들)
                          from s in c.Score     // 새로운 범위 변수 s(배열이다)
                          where s < 60          // 배열중에서 점수가 60보다 작은것
                          orderby s             // 오름차순으로
                          select new { c.Name, Lowest = s };
                          //즉석에서 무명타입을 만듬 , 반이름과 점수를 classes에 담음
            foreach (var c in classes)  // AnonymousType c
                WriteLine("낙제 : {0} ({1})", c.Name, c.Lowest);

            //낙제: 노랑반(0)
            //낙제: 노랑반(17)
            //낙제: 연두반(24)
            //낙제: 파랑반(30)
            //낙제: 분홍반(45)
        }
    }
}
