using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using static System.Console;

namespace ConsoleApp1
{
    class Profile
    {
        public string Name { get; set; }
        public int Height { get; set; }
    }
    class Product
    {
        public string Title { get; set; }
        public string Star { get; set; }
    }
    class MainApp
    {
        static void Main(string[] args)
        {
            Profile[] arrProfile = {
                new Profile(){Name = "정우성", Height = 186},
                new Profile(){Name = "김태희", Height = 158},
                new Profile(){Name = "고현정", Height = 172},
                new Profile(){Name = "이문세", Height = 178},
                new Profile(){Name = "하하", Height = 171},
            };

            Product[] arrProduct = {
                new Product(){Title="비트", Star = "정우성"},
                new Product(){Title="CF 다수", Star = "김태희"},
                new Product(){Title="아이리스", Star = "김태희"},
                new Product(){Title="모래시계", Star = "고현정"},
                new Product(){Title="Solo 예찬", Star = "이문세"},
            };

            // 내부조인
            var listProfile = from profile in arrProfile
                              join product in arrProduct on profile.Name equals product.Star
                              select new
                              {
                                  Name = profile.Name,
                                  Work = product.Title,
                                  Height = profile.Height
                              };
            // 내부조인 결과
            WriteLine("\n내부조인 결과");
            foreach (var profile in listProfile)
            {
                WriteLine($"{profile.Name}, {profile.Work}, {profile.Height}");
            }
            //내부조인 결과
            //정우성, 비트, 186
            //김태희, CF 다수, 158
            //김태희, 아이리스, 158
            //고현정, 모래시계, 172
            //이문세, Solo 예찬, 178

            // 외부조인
            listProfile = from profile in arrProfile
                          join product in arrProduct on profile.Name equals product.Star
                          into ps   //임시컬렉션 
                          from product in ps.DefaultIfEmpty(new Product() { Title = "그런거없음" })
                          select new
                          {
                              Name = profile.Name,
                              Work = product.Title,
                              Height = profile.Height
                          };
            // 외부조인 결과
            WriteLine("\n외부조인 결과");
            foreach (var profile in listProfile)
            {
                WriteLine($"{profile.Name}, {profile.Work}, {profile.Height}");
            }
            //외부조인 결과
            //정우성, 비트, 186
            //김태희, CF 다수, 158
            //김태희, 아이리스, 158
            //고현정, 모래시계, 172
            //이문세, Solo 예찬, 178
            //하하, 그런거없음, 171
        }
    }
}
