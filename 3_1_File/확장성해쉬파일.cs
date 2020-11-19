using System;
using System.Collections.Generic;
using static System.Console;

//레코드 개수 50개
//버킷의 크기 3
//최소 필요 버킷 개수 17개..
//동적해싱,least signficant bits

namespace 화철과제
{

    static class Directory
    {
        public static List<Bucket> entry;
        public static int global_depth;

        static Directory()
        { // 정적 생성자
            global_depth = 1;   // 초기 전역 깊이는 1
            entry = new List<Bucket>(); // 버킷을 담는 entry 배열 생성
            entry.Add(new Bucket(global_depth));   // 초기에는 버킷을 두개 가지므로
            entry.Add(new Bucket(global_depth));   // 두개의 버킷 객체를 생성한후 entry에 넣어준다.
        }

        // 삽입 함수
        public static void Insert_record(record r)
        {
            ushort hashName = Program.get_hash(r, global_depth);    // 현재 레코드의 해쉬값 추출
            entry[hashName].insert_record(r);   // 해쉬네임에 해당하는 버킷의 객체에 가서 삽입 함수 호출
        }

        // 버킷만 확장
        public static void Only_Bucket(record r)
        {
            ushort hashName = Program.get_hash(r, global_depth);    // 해쉬값 추출
            Bucket tempBucket = entry[hashName];    // 오버플로우가 발생한 버킷의 참조를 임시 저장

            // 2^(전역깊이 - 지역깊이) 만큼 디렉토리 엔트리들이 가리키고 있다.
            int point_count = (int)Math.Pow(2, (global_depth - tempBucket.local_depth));

            // 절반만 분할한다 분할에 앞서 기존 버킷의 지역깊이를 수정해주고
            // 새로운 버킷을 생성해준다. 새로운 버킷의 지역깊이는
            // 기존 버킷의  수정된 지역깊이와 같다
            tempBucket.local_depth++;   // 버킷이 분할될 때 지역 깊이는 증가한다
            Bucket newBucket = new Bucket(tempBucket.local_depth);  // 새로운 버킷
            int count = 0, i = 0;
            while (count < point_count / 2)
            {
                if (entry[i] == tempBucket)
                {   // 엔트리가 기존 버킷을 가리키고 있다면
                    entry[i] = newBucket;   //엔트리가 새로운 버킷을 가리키게 한다
                    count++;                // 새로운 버킷을 가리키는 엔트리의 개수를 카운트한다
                }
                i++;
            }

            List<record> will_reHashing = new List<record>();
            for (int k = 0; k < tempBucket.bucket.Count; k++)
            { // 기존 버킷에 있는 레코드를 전부 빼낸다
                will_reHashing.Add(tempBucket.bucket[k]);
            }
            will_reHashing.Add(r);  // 새롭게 추가할 레코드도 저장한다.
            tempBucket.bucket.Clear();  // 기존 버킷을 비운다

            // 기존 버킷에 있던 레코드와 추가된 레코드의 재삽입을 시도한다
            for (int z = 0; z < will_reHashing.Count; z++)
            {
                int hash = Program.get_hash(will_reHashing[z], global_depth);
                entry[hash].insert_record(will_reHashing[z]);
            }

        }

        // 디렉토리와 버킷 확장
        public static void Directory_and_Bucket(record r) {
            // 디렉토리를 두배로 확장한 후 오버플로우 버킷만 분할하면 되지 않을까?

            // 디렉토리 확장을 시도한다
            int beforeEntryCount = (int)Math.Pow(2, global_depth);  // 기존 엔트리 개수 구함
            global_depth++; // 전역 깊이 1 증가시킨다
            int afterEntryCount =  (int)Math.Pow(2, global_depth);  // 확장된 엔트리 개수 구함

            // 추가되는 엔트리들이 기존의 엔트리가 가리키는것을 가리키게 한다
            // 그냥 첫번째부터 마지막까지 순서대로 추가하면 된다
            for (int i = 0; i < beforeEntryCount; i++) {
                entry.Add(entry[i]);
            }
            // 디렉토리만 확장시 버킷들의 지역깊이에는 영향이 없다

            // 버킷 확장을 시도한다
            Only_Bucket(r);
        }


    }

    static class BucketSet
    {
        public static List<Bucket> bucketSet = new List<Bucket>();
        public static void ShowBucketSet()
        {

            WriteLine($"\n전역 깊이 = {Directory.global_depth}, 버킷 개수 = {bucketSet.Count}");

            WriteLine("\n각 엔트리들이 가리키는 버킷들");
            for (int k = 0; k < (int)Math.Pow(2, Directory.global_depth); k++) {
                for (int j = 0; j < bucketSet.Count; j++)
                {
                    if(Directory.entry[k] == bucketSet[j])
                    WriteLine($"--entry{k}  -->>  {j} 번 버킷");
                }
            }
            WriteLine();

            for (int i = 0; i < bucketSet.Count; i++)
            {
                Bucket tempBucket = bucketSet[i];
                WriteLine($"~~~~~{i}번 버킷~~~~~~~~~~~~~~~버킷의지역깊이 {tempBucket.local_depth}");
                for (int j = 0; j < bucketSet[i].bucket.Count; j++)
                {
                    Write("{0}  ,,  ",tempBucket.bucket[j].name);
                    Write("{0}  ,,  ", tempBucket.bucket[j].address );
                    Write("{0}  ,,  ", tempBucket.bucket[j].department );
                    WriteLine("{0}  ,,  ", tempBucket.bucket[j].phoneNumber);
                }
                WriteLine("~~~~~{0}번 버킷~~~~~~~~~~~~~~~~end\n", i);
            }
        }
    }

    class Bucket
    {
        public const int BUCKETLIMIT = 3;
        public List<record> bucket;    //레코드 저장  부분
        public int local_depth;
        public Bucket(int local_depth)
        {// 생성자
            bucket = new List<record>();        // List 생성
            this.local_depth = local_depth;     // 전달받은 수로 local_depth 설정
            BucketSet.bucketSet.Add(this);      // Bucket이 생성될때 자기 자신을 bucketSet에 추가.
        }
        public void insert_record(record r)
        {
            if (bucket.Count < BUCKETLIMIT)
            {   // 현재 버킷의 멤버수가 3보다 작을 경우 그냥 삽입
                //WriteLine("그냥 삽입");
                bucket.Add(r);
            }
            else  // 오버플로우 경우
            {
                if (Directory.global_depth >= local_depth + 1)          // 버킷만 분할
                {
                    WriteLine("버킷만 분할");
                    Directory.Only_Bucket(r);
                }
                else if (Directory.global_depth < local_depth + 1)      // 디렉토리 확장, 버킷 분할, 
                {
                    WriteLine("디렉토리와 버킷 분할");
                    Directory.Directory_and_Bucket(r);
                }
            }
        }
    }
    struct record
    {
        public string name;        //이름
        public string address;     //주소
        public string department;  //학과
        public string phoneNumber; //전화번호
        public record(string name, string address, string department, string phoneNumber)
        {
            this.name = name; this.address = address; this.department = department; this.phoneNumber = phoneNumber;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            record[] rSet = new record[50];
            rSet[0] = new record("박서원", "서울시 양천구", "컴퓨터과학부", "01036110283");
            rSet[1] = new record("홍길동", "서울시 강서구", "전전컴", "18883456");
            rSet[2] = new record("임창정", "서울시 강북구", "가수부", "36111234670283");
            rSet[3] = new record("강호동", "서울시 강동구", "연예부", "123214654356");
            rSet[4] = new record("유재석", "인천시 양천구", "연예부", "361754310283");
            rSet[5] = new record("이수근", "서원시 강서구", "연예부", "123413456");
            rSet[6] = new record("엠씨몽", "면제시 양천구", "가수부", "361764510283");
            rSet[7] = new record("사나", "트와이스시 강서구", "가수부", "1212433456");
            rSet[8] = new record("미나", "서울시 양천구", "가수부", "361102812343");
            rSet[9] = new record("쯔위", "일본 트와이스시", "가수부", "12123431234456");
            rSet[10] = new record("구하라", "서울시 양천구", "가수부", "36110124283");
            rSet[11] = new record("니콜", "서울시 카라구", "가수부", "1124321243456");
            rSet[12] = new record("동방신기", "서울시 양천구", "가수부부", "361124310283");
            rSet[13] = new record("방탄소년단", "서울시 강서구", "가수부", "1283456");
            rSet[14] = new record("이동규", "서울시 양천구", "운전부", "3611068283");
            rSet[15] = new record("이짝규", "서울시 강서구", "비어킹부", "1234123456");
            rSet[16] = new record("이큰규", "서울시 양천구", "컴퓨터과학부", "361105143283");
            rSet[17] = new record("김지훈", "서울시 강서구", "토토부", "126734576");
            rSet[18] = new record("박설희", "서울시 양천구", "컴퓨터과학부", "123436110283");
            rSet[19] = new record("이진형", "서울시 양천구", "물리부", "12343256");
            rSet[20] = new record("권순규", "서울시 목동", "부비부비부", "366454110283");
            rSet[21] = new record("이현주", "서울시 까치산", "컴퓨터보안부", "123123456");
            rSet[22] = new record("김정민", "서울시 고기구", "고기집부", "36110212383");
            rSet[23] = new record("김상욱", "경기도 의정부", "국카스텐부", "123123456");
            rSet[24] = new record("김민욱", "경기도 성악구", "알토 성악부", "31236110212383");
            rSet[25] = new record("배철수", "서울시 강서구", "라디오부", "1231234562");
            rSet[26] = new record("유인나", "서울시 양천구", "라디오부", "36111230283");
            rSet[27] = new record("박보영", "서원시 서원구", "배우부", "123423456");
            rSet[28] = new record("니콜키드먼", "미국 워싱턴", "가수부", "36113420283");
            rSet[29] = new record("깁스", "NCIS", "특수요원부", "123476556");
            rSet[30] = new record("맥기", "NCIS", "특수요원부", "36110283");
            rSet[31] = new record("토니디노조", "NCIS", "매우특수요원부", "12341357856");
            rSet[32] = new record("지바다비드", "NCIS", "특수요원부", "3611028783");
            rSet[33] = new record("애비슈토", "NCIS", "특수요원부", "1234123456");
            rSet[34] = new record("일라이다비드", "NCIS", "모사드부", "3611023283");
            rSet[35] = new record("트와이스", "제이와이피", "아이돌부", "123678456");
            rSet[36] = new record("모모", "일본 오사카", "컴퓨터과학부", "36110283");
            rSet[37] = new record("양팡", "경상도 부산", "비제이부부", "1234123456");
            rSet[38] = new record("햅번", "서울시 소사동", "이상형부", "3611043283");
            rSet[39] = new record("따규", "서울시 소사동", "스타부", "12343356");
            rSet[40] = new record("홍구", "충청도 스타구", "스타부", "361101234283");
            rSet[41] = new record("서나래", "서울시 잠실", "웹툰부", "1233456");
            rSet[42] = new record("나나야시키", "일본 나가사키", "토오노시키부", "33446110283");
            rSet[43] = new record("나루토", "서울시 마포구", "나뭇잎마을", "1234213456");
            rSet[44] = new record("코우가", "경기도 일산", "컴퓨터과학부", "361123410283");
            rSet[45] = new record("이치고", "서울시 백구", "사신부", "123456");
            rSet[46] = new record("아카츠키", "서울시 강동구", "오로치마루부", "3611612340283");
            rSet[47] = new record("이문세", "서울시 구로구", "라디오부", "12342456");
            rSet[48] = new record("남진", "서울시 동작구", "트로트부", "312336110283");
            rSet[49] = new record("서태지", "서울시 옛날구", "가수부", "123423456");


            for (int i = 0; i < 50; i++)
            {
                //WriteLine("{0}번째 삽입", i);
                Directory.Insert_record(rSet[i]);
            }

            BucketSet.ShowBucketSet();
        }


        // 해쉬값의 길이는 16bit
        // MD5 모형과 비슷하게 해쉬함수 작성
        static ushort UnsignedLeftShift(ushort number, int shift)
        {// 좌 쉬프트 연산
            return (ushort)((number << shift) | (number >> (32 - shift)));
        }
        public const int maxHashLength = 16;
        public static ushort get_hash(record r, int depth) //depth길이만큼만 반환
        {
            string str = r.name;
            int n = str.Length; //str의 길이
            ushort[] result = new ushort[n];

            for (int i = 0; i < n; i++)
            {
                char ch = str[i % n];
                // char는 c#에서 2byte=16bit
                // str[i]를 이용하여 4개의 16bit 단어를 만들자
                ushort a = (ushort)(ch ^ 0x048c);
                ushort b = (ushort)(ch ^ 0x159d);
                ushort c = (ushort)(ch ^ 0x26ae);
                ushort d = (ushort)(ch ^ 0x37bf);
                // WriteLine("{0:x} {1:x} {2:x} {3:x}", a, b, c, d);

                // 기약함수
                ushort f = 0;
                switch (i % 4)
                {
                    case 0:
                        f = (ushort)((b & c) | (~b & d));
                        break;
                    case 1:
                        f = (ushort)((b & d) | (c & ~d));
                        break;
                    case 2:
                        f = (ushort)(b ^ c ^ d);
                        break;
                    case 3:
                        f = (ushort)(c ^ (b & ~d));
                        break;
                }

                ushort X = (ushort)str[(i + 1) % n];
                ushort T = (ushort)str[(i + 2) % n];

                ushort b1 = (ushort)(a + f);
                b1 = (ushort)(b1 + f);
                b1 = (ushort)(b1 + X);
                b1 = (ushort)(b1 + T);
                b1 = UnsignedLeftShift(b1, i);
                b1 = (ushort)(b + b1);

                a = d;
                d = c;
                c = b;
                b = b1;

                // WriteLine("{0:x4} {1:x4} {2:x4} {3:x4}", a, b, c, d);
                ushort ret = (ushort)(a ^ b ^ c ^ d);
                ret = UnsignedLeftShift(ret, 1);

                // str의 한 단어들을 알고리즘을 돌린후 result에 하나씩 저장한다.
                result[i % n] = ret;
            }

            ushort hash = 0;
            for (int i = 0; i < n; i++)
            {// 저장되있는 result들을 xor연산         
                hash = (ushort)(hash ^ result[i]);
                hash = (ushort)(hash | i);
                hash = (ushort)((hash + (ushort)(hash % 3)) % ushort.MaxValue);
            }
            ushort ret1 = 0;
            for (int i = 0; i < depth; i++)
            {
                ret1 = (ushort)(ret1 + ((ushort)Math.Pow(2, i) & (ushort)hash));
            }
            return ret1;

        }
    }
}