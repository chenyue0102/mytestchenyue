using System.IO;
using System.Linq;
using System.Runtime.Serialization.Json;
using System.Text;


public static class JSON
{
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
