using System;

namespace StringArray
{
    class Program
    {
        const int SIZE = 5;
        
        static void Main(string[] args)
        {
            string[] array = new string[SIZE];

            for (int i = 0; i < array.Length; i++) {
                Console.Write("Entre com a " + (i + 1) + "a. palavra: ");
                array[i] = Console.ReadLine();
            }

            Console.Write("Array com valores strings lidos: \n");
            Console.Write("[");

            for (int i = 0; i < array.Length; i++) {
                Console.Write(array[i] + ",");
            }

            Console.Write("]\n");
        }
    }
}