using System;
using System.Collections.Generic;
using System.Reflection;
using UnityEngine;

public abstract class MessageBriageReceive : MonoSingleton<MessageBriage>
{
    public static string UNITY_RECEIVE_OBJECT_NAME = "MessageBriage";
    public delegate void MsgHandler(int msgId, string msgText);
    public class MessageHeader
    {
        public int msgId = 0;
    }
    private class WeakDelegate
    {
        public WeakReference Target;
        public MethodInfo Meghod;
    }
    private Dictionary<int, List<WeakDelegate>> messageProcess;


    protected override void Init()
    {
        messageProcess = new Dictionary<int, List<WeakDelegate>>();
        gameObject.name = UNITY_RECEIVE_OBJECT_NAME;
    }

    public abstract void SendMessageToApp(string paramText);

    public void RegMsg(int msgId, MsgHandler process)
    {
        WeakDelegate weakDelegate = new WeakDelegate();
        weakDelegate.Meghod = process.Method;
        weakDelegate.Target = new WeakReference(process.Target);
        if (messageProcess.ContainsKey(msgId))
        {
            messageProcess[msgId].Add(weakDelegate);
        }
        else
        {
            List<WeakDelegate> list = new List<WeakDelegate>();
            list.Add(weakDelegate);
            messageProcess.Add(msgId, list);
        }
    }

    public void OnAppMessage(string msgText)
    {
        do
        {
            Debug.Log(msgText);
            MessageHeader messageHeader = JSON.fromString<MessageHeader>(msgText);
            if (null == messageHeader)
            {
                Debug.Log("MessageBriageBase OnAppMessage null == messageHeader failed");
                break;
            }
            if (!messageProcess.ContainsKey(messageHeader.msgId))
            {
                Debug.Log("MessageBriageBase OnAppMessage msgId failed");
                break;
            }
            List<WeakDelegate> list = messageProcess[messageHeader.msgId];
            for (int i = list.Count - 1; i >= 0; i--)
            {
                WeakDelegate item = list[i];
                object target = item.Target.Target;
                if (null != target)
                {
                    item.Meghod.Invoke(target, new object[] {messageHeader.msgId, msgText});
                }
                else
                {
                    list.RemoveAt(i);
                }
            }
        } while (false);
    }
}
