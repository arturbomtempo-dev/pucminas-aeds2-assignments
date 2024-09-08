using System;

namespace ClassArray {
    class User {    
        public string name;    
        public int age;    
        public string country;
    }

    class Program {
        static void Main(string[] args) {
            User[] users = {
                new User { name = "Homer Simpson", age = 42, country = "USA" },
                new User { name = "Marge Simpson", age = 38, country = "USA"},
                new User { name = "Bart Simpson", age = 19, country = "USA"},
                new User { name = "Lisa Simpson", age = 17, country = "USA"}, 
            };

            foreach (User user in users) {
                Console.WriteLine(user.name + " - " + user.age);
            }
        }
    }
}