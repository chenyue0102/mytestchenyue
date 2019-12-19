package com.example.myapplication;


import android.app.Service;
import android.content.Intent;
import android.os.ConditionVariable;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.util.Log;
import android.widget.MultiAutoCompleteTextView;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class SocketClient extends Service {
    public Handler m_uiHandler;
    public String m_strSendText = new String();
    public Lock m_lock = new ReentrantLock();
    public Condition m_cv = m_lock.newCondition();
    public Thread m_thd;
    SocketClient(Handler h)
    {
        m_uiHandler = h;
    }
    @Override
    public void onCreate()
    {
        super.onCreate();
        m_thd = new Thread(new Runnable() {
            @Override
            public void run() {
                Log.i("SocketClient", "run");
                process();
            }
        });
    }
    @Override
    public IBinder onBind(Intent intent){
        throw new UnsupportedOperationException("Not yet implemented");
    }
    public void sendText(String text)
    {
        m_lock.lock();
        m_strSendText = text;
        m_cv.signal();
        m_lock.unlock();
    }
    public void process() {
        Socket s = null;
        try{
            s = new Socket("localhost", MainActivity.CONNECT_PORT);
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(s.getOutputStream())));
            while(true)
            {
                try
                {
                    m_lock.lock();
                    m_cv.await();
                    out.println(m_strSendText);
                    m_lock.unlock();

                    String str = in.readLine();
                    Message msg = m_uiHandler.obtainMessage(MainActivity.MSGID_INSERT_TEXT, str);
                    m_uiHandler.dispatchMessage(msg);

                }catch (InterruptedException e)
                {
                    e.printStackTrace();
                    m_lock.unlock();
                }
            }
        }catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
