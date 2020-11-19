using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    interface IGenericInterface<T>
    {
        void SetValue(T x);
        string GetValueType();
    }
    class GenericClass<T> : IGenericInterface<T>
    {
        private T value;
        public void SetValue(T x) { value = x; }
        public String GetValueType() { return value.GetType().ToString(); }
    }
    class Program
    {
        public static void Main(string[] args)
        {
            GenericClass<int> gInteger = new GenericClass<int>();
            GenericClass<String> gString = new GenericClass<string>();
            gInteger.SetValue(16); gString.SetValue("Text");
            WriteLine(gInteger.GetValueType());
            WriteLine(gString.GetValueType());
        }
    }
}
