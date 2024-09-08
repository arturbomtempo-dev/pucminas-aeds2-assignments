using System;

namespace BinarySearch {
    class Program {
        static bool BinarySearch(int[] array, int x) {
            bool found = false;
            int left = 0, right = array.Length - 1, middle;

            while (left <= right && !found) {
                middle = (left + right) / 2;

                if (array[middle] == x) {
                    found = true;
                } else if (x > array[middle]) {
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            }

            return found;
        }

        static void Main(string[] args) {
            Random random = new Random();
            int[] array = new int[100];

            for (int i = 0; i < array.Length; i++) {
                array[i] = random.Next(1, 201);
            }

            Array.Sort(array);

            Console.WriteLine("Valores do array ordenados: ");
            
            foreach (int value in array) {
                Console.Write(value + " ");
            }

            Console.WriteLine();

            Console.Write("Digite o número a ser pesquisado: ");
            int number = int.Parse(Console.ReadLine());

            bool result = BinarySearch(array, number);

            if (result) {
                Console.WriteLine($"Número {number} encontrado no array.");
            } else {
                Console.WriteLine($"Número {number} não encontrado no array.");
            }
        }
    }
}