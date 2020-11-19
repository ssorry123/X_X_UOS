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

            var listProfile = from profile in arrProfile
                              orderby profile.Height    // 키로 정렬
                              group profile by profile.Height < 175 into g
                              select new { GroupKey = g.Key, Profiles = g };
            // g에는 175미만인 객체 컬렉션과   175이상인 객체컬렉션 입력
            // 무명형식의 Profiles 필드는 그룹 변수 g를 담는다
            // 셀렉트가 추출하는 새로운 무명형식은 컬렉션의 컬렉션이 된다
            foreach (var Group in listProfile)
            {    // Group은 IGrouping<T> 형식
                WriteLine($"-175cm 미만? : {Group.GroupKey}");    // True
                foreach (var profile in Group.Profiles)
                    WriteLine($"\t{profile.Name}, {profile.Height}");
            }
            //-175cm 미만? : True
            //김태희, 158
            //하하, 171
            //고현정, 172
            //- 175cm 미만? : False
            //이문세, 178
            //정우성, 186
        }
    }
}
