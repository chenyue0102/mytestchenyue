#if UNITY_EDITOR

using UnityEngine;

public class MessageBriage : MessageBriageReceive
{
    protected override void Init()
    {
        base.Init();
    }

    public override void SendMessageToApp(string paramText)
    {
        Debug.Log("MessageBriage SendMessageToApp " + paramText);
    }
}
#endif
