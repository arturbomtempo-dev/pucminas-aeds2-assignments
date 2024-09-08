using System;

namespace IntegerArray
{
    class Program
    {
        const int SIZE = 10;
        
        static void Main(string[] args)
        {
            int[] array = new int[SIZE];
            Random random = new Random();

            for (int i = 0; i < SIZE; i++) {
                array[i] = random.Next(10);
            }

            Console.Write("Array com valores inteiros: \n");
            Console.Write("[ ");

            for(int i = 0; i < SIZE; i++) {
                Console.Write(array[i] + ", ");
            }

            Console.Write("]\n");
        }
    }
}