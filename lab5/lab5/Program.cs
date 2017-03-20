using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace lab5
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Enter the first number\n");
            string string_number1 = Console.ReadLine();
            Console.WriteLine("Enter the second number\n");
            string string_number2 = Console.ReadLine();
            LongNumber number1 = new LongNumber(string_number1);
            LongNumber number2 = new LongNumber(string_number2);
            if(LongNumber.MuTuallySimple(number1, number2))
            {
                Console.WriteLine("\nMutually simple\n");
            } 
            else
            {

                Console.WriteLine("\nNot mutually simple\n");
            }


            Console.ReadKey();
        }
    }
}
