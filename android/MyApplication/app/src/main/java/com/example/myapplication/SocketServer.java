package com.example.myapplication;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

import com.example.myapplication.MainActivity;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicBoolean;

public class SocketServer extends Service {
    public AtomicBoolean m_bExit;
    @Override
    public IBinder onBind(Intent intent){
        throw new UnsupportedOperationException("Not yet implemented");
    }
    @Override
    public void onCreate(){
        super.onCreate();
        m_bExit = new AtomicBoolean(false);
        new Thread(new Runnable() {
            @Override
            public void run() {
                ServerSocket s = null;
                try{
                    s = new ServerSocket(MainActivity.CONNECT_PORT);
                    final Socket client =  s.accept();
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            try{
                                processClient(client);
                            }catch (IOException e)
                            {
                                e.printStackTrace();
                            }
                        }
                    });
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        });
    }
    private void processClient(Socket client)throws IOException
    {
        Log.i("SocketServer", "processClient" );
        BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())));
        while (client.isConnected())
        {
            String str = in.readLine();
            out.println("回馈消息" + str);
        }
        in.close();
        out.close();
        client.close();
    }
}
