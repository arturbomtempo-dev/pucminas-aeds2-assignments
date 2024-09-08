using System;

namespace FindMethod
{
    class Program
    {
        static void Main(string[] args)
        {
            String[] array = { "Rato", "Sapo", "Sapato", "Ratoeira", "Mato"};
            String prefix;

            Console.Write("Entre com o prefixo para pesquisa: ");
            prefix = Console.ReadLine();

            String[] response = Array.FindAll(array, item => item.StartsWith(prefix));

            foreach(String word in response) {
                Console.WriteLine(word);
            }
        }
    }
}