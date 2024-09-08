using System;

namespace SequentialSearch
{
    class Program
    {
        static bool SequentialSearch(int[] array, int x)
        {
            bool found = false;
            
            for (int i = 0; i < array.Length; i++) {
                if (array[i] == x) {
                    found = true;
                    i = array.Length;
                }
            }

            return found;
        }

        static void Main(string[] args)
        {
            Random random = new Random();
            int[] array = new int[10];

            for (int i = 0; i < array.Length; i++) {
                array[i] = random.Next(0, 101);
            }

            Console.WriteLine("Valores do array: ");
            
            foreach (int value in array) {
                Console.Write(value + " ");
            }

            Console.WriteLine();

            Console.Write("Digite o número a ser pesquisado: ");
            int number = int.Parse(Console.ReadLine());

            bool result = SequentialSearch(array, number);

            if (result) {
                Console.WriteLine($"Número {number} encontrado no array.");
            } else {
                Console.WriteLine($"Número {number} não encontrado no array.");
            }
        }
    }
}