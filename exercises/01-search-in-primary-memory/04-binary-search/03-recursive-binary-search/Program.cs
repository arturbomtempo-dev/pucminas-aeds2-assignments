using System;

namespace RecursiveBinarySearch {
    class Program {
        public static int BinarySearchRecursive(int[] array, int x, int left, int right) {
            if (left > right) {
                return -1;
            } else {
                int middle = (left + right) / 2;

                if (x == array[middle]) {
                    return middle;
                } else if (x > array[middle]) {
                    return BinarySearchRecursive(array, x, middle + 1, right);
                } else {
                    return BinarySearchRecursive(array, x, left, middle - 1);
                }
            }
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
            int number;

            if (int.TryParse(Console.ReadLine(), out number)) {
                int result = BinarySearchRecursive(array, number, 0, array.Length - 1);

                if (result != -1) {
                    Console.WriteLine($"Número {number} encontrado na posição {result}.");
                } else {
                    Console.WriteLine($"Número {number} não encontrado no array.");
                }
            } else {
                Console.WriteLine("Valor inserido inválido. Digite um número válido.");
            }
        }
    }
}