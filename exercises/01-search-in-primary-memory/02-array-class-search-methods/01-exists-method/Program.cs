using System;
using System.Collections.Generic;

namespace ExistsMethod {
    class Student {
        public string name;   
        public int enrollmentCode;

        public override String ToString(){
            return name + " - " + enrollmentCode;
        }
    }

    class Program {
        public static void Menu() {
            Console.WriteLine("1 - Para cadastrar aluno");
            Console.WriteLine("2 - Para pesquisar aluno");
            Console.WriteLine("3 - Para mostrar todos alunos");
            Console.WriteLine("4 - Para sair");
        }

        static void Main(string[] args) {
            List<Student> students = new List<Student>();
            int option;
            Menu();
            option = Int32.Parse(Console.ReadLine());

            while (option != 4) {
                switch (option){
                    case 1:
                        Student student = new Student();

                        Console.WriteLine("Informe o nome do aluno");
                        student.name = Console.ReadLine();

                        Console.WriteLine("Informe o número de matricula");
                        student.enrollmentCode = Int32.Parse(Console.ReadLine());

                        students.Add(student);

                        break;
                    case 2:
                        Console.WriteLine("Informe o numero de matricula: ");

                        int enrollmentCode = Int32.Parse(Console.ReadLine());

                        if (students.Exists(item => item.enrollmentCode == enrollmentCode)) {
                            Console.WriteLine("Aluno cadastrado!!!");
                        } else {
                            Console.WriteLine("Aluno não cadastrado!!!");
                        }

                        break;

                    case 3:
                        foreach (Student item in students) {
                            Console.WriteLine(item.ToString());
                        }

                        break;
                }

                Console.ReadKey();
                Console.Clear();

                Menu();
                option = Int32.Parse(Console.ReadLine());
            }
        }
    }
}