using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 윈도우즈프로그래밍
{
    public class Color
    {
        public const Int32 FULL = 0xFF;
        public const Int32 EMPTY = 0x00;
        private byte red, green, blue;
        //read only fields;
        // 클래스의 static 필드는 클래스의 객체를 필드로 가진다.
        public static readonly Color Red = new Color(FULL, EMPTY, EMPTY);
        // public readonly Color Red = new Color(FULL, EMPTY, EMPTY);
        public static readonly Color Green = new Color(EMPTY, FULL, EMPTY);
        public static readonly Color Blue = new Color(EMPTY, EMPTY, FULL);
        // static 필드가 아니라면 어떻게 될까?
        // Color 객체 생성시 필드에서는 또 객체를 생성하고
        // 그 객체는 또 객체를 생성하고,, 무한 루프에 빠진다.
        //스택오버플로우 예외가 발생한다.
        //Process is terminated due to StackOverflowException.
        public Color(byte r, byte g, byte b)
        {
            red = r;
            green = g;
            blue = b;
        }
        public static void PrintColor(Color c)
        {
            WriteLine("Red value = {0}, green value = {1}, blue value={2}", c.red, c.green, c.blue);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            WriteLine("FULL = " + Color.FULL);
            //Color c = new Color(0xff,0xff,0xff);
            Color.PrintColor(Color.Red);
        }
    }
}
