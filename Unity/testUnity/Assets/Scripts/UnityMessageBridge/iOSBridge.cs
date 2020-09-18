#if UNITY_IPHONE && !UNITY_EDITOR
using UnityEngine;
using System.Runtime.InteropServices;

public class MessageBriage : MessageBriageReceive
{
    [DllImport("__Internal")]
    private static extern void onUnityMessage(string msgText);



    protected override void Init()
    {
        base.Init();
    }
    
    public override void SendMessageToApp(string paramText)
    {
        onUnityMessage(paramText);
    }
}
#endif