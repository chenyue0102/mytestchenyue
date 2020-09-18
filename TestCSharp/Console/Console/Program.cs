using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization.Json;
using System.Text;



namespace TestConsole
{
    public class Person
    {
        public string name { get; set; }
        public int age { get; set; }

        public List<Person> chidren;
    }

    //public static T parse<T>(string jsonString)
    //{

    //}

    public static class JSON {
        public static string toString(object obj)
        {
            using (var ms = new MemoryStream())
            {
                new DataContractJsonSerializer(obj.GetType()).WriteObject(ms, obj);
                return Encoding.UTF8.GetString(ms.ToArray());
            }
        }

        public static T fromString<T>(string jsonString)
        {
            using (var ms = new MemoryStream(Encoding.UTF8.GetBytes(jsonString)))
            {
                return (T)new DataContractJsonSerializer(typeof(T)).ReadObject(ms);
            }
        }
    }


  

    class Program
    {
        static void Main(string[] args)
        {
            string formatText = string.Format("name:{0}, age:{1}", new object[] { "kitty", 2});
            Console.WriteLine("Hello World!");

            Person person = new Person();
            person.name = "hello, kitty";
            person.age = 2;
            person.chidren = new List<Person>();

            Person tom = new Person();
            tom.name = "tom";
            tom.age = 1;
            person.chidren.Add(tom);

            Person mary = new Person();
            mary.name = "mary";
            mary.age = 0;
            person.chidren.Add(mary);

            string txt = JSON.toString(person);
            Console.WriteLine(txt);

            Person person1 = JSON.fromString<Person>(txt);

            Console.WriteLine(person1.name);
            MessageBriage messageBriage = new MessageBriage();
            messageBriage.printf();
        }
    }
}
