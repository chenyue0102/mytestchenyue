package com.example.myapplication;

import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.IpSecManager;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.RandomAccessFile;
import java.io.UnsupportedEncodingException;
import java.lang.reflect.Field;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.function.Predicate;

import com.example.myapplication.SocketClient;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import static android.content.Context.WIFI_SERVICE;

public class MainActivity extends AppCompatActivity {

    public TextView m_LogView;
    public Handler m_handler;
    public static final int MSGID_INSERT_TEXT = 8000;
    public static final int CONNECT_PORT = 18989;

    public String m_strSendText = new String();
    public Lock m_lock = new ReentrantLock();
    public Condition m_cv = m_lock.newCondition();

    private class MyBroadcastReceiver extends BroadcastReceiver
    {
        @Override
        public void onReceive(Context context, Intent intent) {
            Toast.makeText(context, "myReceiver receive", Toast.LENGTH_SHORT).show();
            WifiManager wifiManager = (WifiManager )getApplicationContext().getSystemService(WIFI_SERVICE);
            List<ScanResult> sr =  wifiManager.getScanResults();
            sr.size();
        }
    }

    public void testWIFI()throws Exception
    {
        WifiManager wifiManager = (WifiManager )getApplicationContext().getSystemService(WIFI_SERVICE);
        //wifiManager.setWifiEnabled(false);
        int state = wifiManager.getWifiState();
        //当前wifi信息
        WifiInfo info = wifiManager.getConnectionInfo();
        String ssid = info.getSSID() + info.getBSSID();
        Log.i("MyTest", ssid);
        IntentFilter filter = new IntentFilter();
        filter.addAction(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
        filter.setPriority(4000);
        MyBroadcastReceiver myrecv = new MyBroadcastReceiver();
        registerReceiver(myrecv, filter);
        wifiManager.startScan();
        List<ScanResult> sr =  wifiManager.getScanResults();
        //连接过WIFI配置
        List<WifiConfiguration> wc = wifiManager.getConfiguredNetworks();
        sr.size();
    }
    public void testBroadcast()throws Exception
    {
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                DatagramSocket socket = null;
                DatagramPacket sendPacket = null;
                String str = "hello world";
                byte b[] = null;
                try{
                    b = str.getBytes("utf-8");
                    socket = new DatagramSocket(null);
                    socket.setBroadcast(true);
                    socket.setReuseAddress(true);
                    socket.bind(new InetSocketAddress(CONNECT_PORT));
                    sendPacket = new DatagramPacket(b, b.length, InetAddress.getByName("255.255.255.255"), 17777);
                    while (true){
                        socket.send(sendPacket);
                        Thread.sleep(200);
                    }
                }catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        });

        t.start();
    }

    public static class Parent{
        public transient String parent = "parent";
    }
    public static class StructTemplate<T>{
        public String parent;
        public T result;
    }
    public static class Child extends Parent{
        public String child = "child";
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Child child = new Child();
        Parent parent = child;

        StructTemplate<Parent> jsonParent = new StructTemplate<>();
        jsonParent.result = parent;
        jsonParent.parent = parent.parent;
        Gson gson = new Gson();
        String childJson = gson.toJson(jsonParent);
        Log.i("tag", childJson);


        try{
            testWIFI();
            testBroadcast();
        }catch (Exception e)
        {
            e.printStackTrace();
        }
        test ts = new test();
        //Log.i("MainActivity", ts.name);
        ts.name = "abc_123";
        String s2[] = ts.name.split("_");
        StringBuffer sb = new StringBuffer("abc");
        sb.append("123");
        String ssss = sb.toString();
        Log.i("MyTest", ssss);

        int a = 3/2;
        int bb = -3/2;
        String sf = getExternalCacheDir().getAbsolutePath() ;
        File f = new File(sf, "test.txt");
        sf = f.getAbsolutePath();
        if (!f.exists())
        {
            try{
                f.createNewFile();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        try{
            FileOutputStream fos = new FileOutputStream(f);
            fos.write("abc123".getBytes("utf-8"));
            fos.close();
            RandomAccessFile raf = new RandomAccessFile(f, "rw");
            raf.seek(raf.length());
            raf.write("random write".getBytes("utf-8"));
            raf.close();
        }catch (Exception e)
        {
            e.printStackTrace();
        }


        try{
            throw new Exception();
        }catch (Exception e)
        {
            e.printStackTrace();
        }finally {
            a = 0;
        }

        Integer ig = new Integer(a);
        Integer ig2 = new Integer(a);
        if (ig == ig2)
        {
            Log.i("MyTest", "ig == ig2");
        }
        if (ig.equals(ig2))
        {
            Log.i("MyTest", "ig equals ig2");
        }
        Vector<String> vs = new Vector<String>();
        vs.add("abc");
        vs.add("123");
        vs.add("def");
        vs.add("xyz");

        for (String s:vs) {
            Log.i("MyTest", s);
        }

        @RequiresApi(api = Build.VERSION_CODES.N)
        class aaa implements Predicate<String>{

            @Override
            public boolean test(String o) {
                return o == "abc" || o == "def";
            }

            @Override
            public Predicate and(Predicate other) {
                return null;
            }

            @Override
            public Predicate negate() {
                return null;
            }

            @Override
            public Predicate or(Predicate other) {
                return null;
            }
        }
        Predicate<String> myFun = (String o)->{return o == "abc" || o == "def";};
        //vs.removeIf(new aaa());
        vs.removeIf(myFun);
        Iterator<String> iter = vs.iterator();
        while (iter.hasNext())
        {
            String s = iter.next();
            if (s == "123")
            {
                iter.remove();
            }
            else
            {
                Log.i("MyTest", s);
            }
        }

        HashMap<Integer, String> is = new HashMap<Integer, String>();
        is.put(100, "abc");
        is.put(200, "def");
        is.put(300, "xyz");
        is.remove(100);

        m_LogView = findViewById(R.id.log);

        Button btnServer = findViewById(R.id.buttonListen);
        btnServer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                createServer();
            }
        });

        Button btnClient  = findViewById(R.id.buttonConnect);
        btnClient.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                //Toast.makeText(getApplicationContext(),"Button onclick2",Toast.LENGTH_SHORT).show();
                createClient();
            }
        });

        m_handler = new Handler(){
            @Override
            public void handleMessage(Message msg){
                super.handleMessage(msg);
                if (msg.what == MSGID_INSERT_TEXT)
                {
                    if (msg.obj instanceof String)
                    {
                        m_LogView.append((String)msg.obj);
                    }
                }
            }
        };
        ByteBuffer bbc = ByteBuffer.allocate(1024);
        bbc.order(ByteOrder.BIG_ENDIAN);
        //Log.i("test", "test");
        //tv1.setText("This is textview 1");
        try{
            Class<SocketClient> obj = SocketClient.class;
            SocketClient s = obj.newInstance();
        }catch (InstantiationException e){
            e.printStackTrace();
        }catch (Exception e){
            e.printStackTrace();
        }

        String str = new String("hello world");
        String str3;
        try{
            byte b[] = str.getBytes("utf-8");
            String str2 = b.toString();
            str3 = new String(b, "utf-8");
        }catch (UnsupportedEncodingException e){
            e.printStackTrace();
        }


        Button btnSend = findViewById(R.id.buttonSendReq);
        btnSend.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                sendText("hello world");
            }
        });
    }
    public void createServer()
    {
        Log.i("MainActivity", "createServer");
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                ServerSocket server = null;
                try{
                    InetAddress addr = InetAddress.getByName("127.0.0.1");
                    server = new ServerSocket( MainActivity.CONNECT_PORT, 50, addr);
                    final Socket client =  server.accept();
                    Log.i("createServer", "accept");
                    Thread t = new Thread(new Runnable() {
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
                    t.start();
                }catch (IOException e){
                    e.printStackTrace();
                }
            }
        });
        t.start();
        //Intent inent = new Intent(this, SocketServer.class);
        //startService(inent);
    }

    public void sendText(String text)
    {
        m_lock.lock();
        m_strSendText = text;
        m_cv.signalAll();
        m_lock.unlock();
    }
    private void processClient(Socket client)throws IOException
    {
        Log.i("SocketServer", "processClient" );
        //BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(client.getOutputStream())));
        InputStream in =  client.getInputStream();
        OutputStream out = client.getOutputStream();
        byte[]b = new byte[1024];
        while (client.isConnected())
        {
            int len = in.read(b);
            String str = "回馈消息:" + new String(b, 0, len, "utf-8");
            Log.i("SocketServer", "processClient"  + str);
            byte sendBuffer[] = str.getBytes("utf-8");
            out.write(sendBuffer);
        }
        in.close();
        out.close();
        client.close();
    }
    public  void createClient()
    {
        Log.i("MainActivity", "createClient");
        //Intent inent = new Intent(this, SocketClient.class);
        //startService(inent);
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                Socket s = null;
                try{
                    s = new Socket("127.0.0.1", MainActivity.CONNECT_PORT);
                    //BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
                    //PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(s.getOutputStream())));
                    InputStream in =  s.getInputStream();
                    OutputStream out = s.getOutputStream();
                    byte b[] = new byte[1024];
                    while(true)
                    {
                        byte tmp[];
                        try
                        {
                            m_lock.lock();
                            m_cv.await();
                            //out.println(m_strSendText + "\r\n");
                            tmp = m_strSendText.getBytes("utf-8");
                            m_lock.unlock();
                            out.write(tmp);
                            int len  = in.read(b);
                            String str = new String(b, 0, len, "utf-8");
                            Message msg = m_handler.obtainMessage(MainActivity.MSGID_INSERT_TEXT, str);
                            m_handler.dispatchMessage(msg);
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
        });
        t.start();
    }

}
