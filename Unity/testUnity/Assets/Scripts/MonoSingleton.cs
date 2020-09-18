using System.CodeDom;
using UnityEngine;

public class MonoSingleton<T> : MonoBehaviour where T : MonoBehaviour
{
    private static T instance = null;

    public static T GetInstance()
    {
        if (null == instance)
        {
            instance = (T)FindObjectOfType(typeof(T));
            if (null == instance)
            {
                new GameObject(typeof(T).Name).AddComponent<T>();
            }
        }
        return instance;
    }

    protected virtual void Awake()
    {
        if (null == instance)
        {
            instance = this as T;
            DontDestroyOnLoad(gameObject);
            Init();
        }else if (instance != this)
        {
            if (instance.gameObject != gameObject)
            {
                Destroy(gameObject);
            }
            else
            {
                Destroy(this);
            }
        }
    }

    protected virtual void onDestroy()
    {
        if (instance == this)
        {
            instance = null;
        }
    }

    protected virtual void Init()
    {

    }
}
