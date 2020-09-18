#if UNITY_ANDROID //&& !UNITY_EDITOR

using UnityEngine;

public class MessageBriage : MessageBriageReceive
{
    private static string APP_BRIAGE_CLASS_NAME = "com.unity3d.player.UnityMessageCallback";
    private static string APP_BRIAGE_METHOD_NAME = "onUnityMessage";
    private AndroidJavaObject androidJavaObject = null;
    

    protected override void Init()
    {
        base.Init();
        if (null == (androidJavaObject = new AndroidJavaObject(APP_BRIAGE_CLASS_NAME)))
        {
            Debug.Log("MessageBriage Init androidJavaObject null failed");
        }
        else
        {
            Debug.Log("MessageBriage Init success");
        }
    }
    
    public override void SendMessageToApp(string paramText)
    {
        if (null != androidJavaObject)
        {
            androidJavaObject.Call(APP_BRIAGE_METHOD_NAME, paramText);
        }
        else
        {
            Debug.Log("MessageBriage SendMessage null == androidJavaObject failed");
        }
    }
}
#endif