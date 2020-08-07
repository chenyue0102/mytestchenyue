package com.test.testcamera;

import android.app.ActivityManager;
import android.content.Context;
import android.os.Environment;
import android.os.StatFs;
import android.text.format.Formatter;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.math.BigDecimal;

public class DeviceUtil {
    /**
     * 获取内存可用空间
     * @return
     */
    public static String getAvailMemory(Context context) {// 获取android当前可用内存大小
        ActivityManager am = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        ActivityManager.MemoryInfo mi = new ActivityManager.MemoryInfo();
        am.getMemoryInfo(mi);
        //mi.availMem; 当前系统的可用内存
        return Formatter.formatFileSize(context, mi.availMem);// 将获取的内存大小规格化
    }

    /**
     * 获取内存总共空间
     * @return
     */
    public static String getTotalMemory(Context context) {
        String str1 = "/proc/meminfo";// 系统内存信息文件
        String str2;
        String[] arrayOfString;
        long initial_memory = 0;
        try {
            FileReader localFileReader = new FileReader(str1);
            BufferedReader localBufferedReader = new BufferedReader(
                    localFileReader, 8192);
            str2 = localBufferedReader.readLine();// 读取meminfo第一行，系统总内存大小

            arrayOfString = str2.split("\\s+");
            for (String num : arrayOfString) {
                Log.e(str2, num + "\t");
            }
            initial_memory = Integer.valueOf(arrayOfString[1]).intValue() * 1024;// 获得系统总内存，单位是KB，乘以1024转换为Byte
            localBufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
        return Formatter.formatFileSize(context, initial_memory);// Byte转换为KB或者MB，内存大小规格化
    }

    public static float getCpuUsed(int pid){
        try {
            BufferedReader readerBB = new BufferedReader(new FileReader("/proc/"));
            String processNameB = readerBB.readLine();
            RandomAccessFile reader2 = new RandomAccessFile("/proc/"+ pid +"/stat", "r");
            String load2 = reader2.readLine();
            String[] toks2 = load2.split(" ");

            double processCpuTime1 = 0.0;
            double utime = Double.parseDouble(toks2[13]);
            double stime = Double.parseDouble(toks2[14]);
            double cutime = Double.parseDouble(toks2[15]);
            double cstime = Double.parseDouble(toks2[16]);

            processCpuTime1 = utime + stime + cutime + cstime;

            try {
                Thread.sleep(360);
            } catch (Exception e) {
                e.printStackTrace();
            }
            reader.seek(0);
            load = reader.readLine();
            reader.close();
            toks = load.split(" ");
            double totalCpuTime2 = 0.0;
            len = toks.length;
            for (int i = 2; i < len; i ++) {
                totalCpuTime2 += Double.parseDouble(toks[i]);
            }
            reader2.seek(0);
            load2 = reader2.readLine();
            String []toks3 = load2.split(" ");

            double processCpuTime2 = 0.0;
            utime = Double.parseDouble(toks3[13]);
            stime = Double.parseDouble(toks3[14]);
            cutime = Double.parseDouble(toks3[15]);
            cstime = Double.parseDouble(toks3[16]);

            processCpuTime2 = utime + stime + cutime + cstime;
            double usage = (processCpuTime2 - processCpuTime1) * 100.00
                    / ( totalCpuTime2 - totalCpuTime1);
            BigDecimal b = new BigDecimal(usage);
            double res = b.setScale(2, BigDecimal.ROUND_HALF_UP).doubleValue();
            return res;
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return 0;
    }

    /**
     * 获取cpu使用率
     * @return
     */
    public static float getCpuUsed() {
        try {
            RandomAccessFile reader = new RandomAccessFile("/proc/stat", "r");
            String load = reader.readLine();
            String[] toks = load.split(" ");
            long idle1 = Long.parseLong(toks[5]);
            long cpu1 = Long.parseLong(toks[2]) + Long.parseLong(toks[3]) + Long.parseLong(toks[4])
                    + Long.parseLong(toks[6]) + Long.parseLong(toks[7]) + Long.parseLong(toks[8]);
            try {
                Thread.sleep(360);
            } catch (Exception e) {
                e.printStackTrace();
            }
            reader.seek(0);
            load = reader.readLine();
            reader.close();
            toks = load.split(" ");
            long idle2 = Long.parseLong(toks[5]);
            long cpu2 = Long.parseLong(toks[2]) + Long.parseLong(toks[3]) + Long.parseLong(toks[4])
                    + Long.parseLong(toks[6]) + Long.parseLong(toks[7]) + Long.parseLong(toks[8]);
            return (float) (cpu2 - cpu1) / ((cpu2 + idle2) - (cpu1 + idle1));
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        return 0;
    }


    /**
     * 外部存储是否可用 (存在且具有读写权限)
     */
    public static boolean isExternalStorageAvailable() {
        return Environment.getExternalStorageState().equals(
                Environment.MEDIA_MOUNTED);
    }

    /**
     * 获取手机内部可用空间大小
     * @return
     */
    static public String getAvailableInternalMemorySize(Context context) {
        File path = Environment.getDataDirectory();
        StatFs stat = new StatFs(path.getPath());
        long blockSize = stat.getBlockSize();
        long availableBlocks = stat.getAvailableBlocks();
        return Formatter.formatFileSize(context,availableBlocks * blockSize);
    }

    /**
     * 获取手机内部空间大小
     * @return
     */
    public static String getTotalInternalMemorySize(Context context) {
        File path = Environment.getDataDirectory();//Gets the Android data directory
        StatFs stat = new StatFs(path.getPath());
        long blockSize = stat.getBlockSize();      //每个block 占字节数
        long totalBlocks = stat.getBlockCount();   //block总数
        return Formatter.formatFileSize(context,totalBlocks * blockSize);
    }


    /**
     * 获取手机外部可用空间大小
     * @return
     */
    public static String getAvailableExternalMemorySize(Context context) {
        if (isExternalStorageAvailable()) {
            StatFs stat = new StatFs(Environment.getExternalStorageDirectory().getAbsolutePath());
            long blockSize = stat.getBlockSize();
            long availableBlocks = stat.getAvailableBlocks();
            return Formatter.formatFileSize(context,availableBlocks * blockSize);
        } else {
            return "-1";
        }
    }

    /**
     * 获取手机外部总空间大小
     * @return
     */
    public static String getTotalExternalMemorySize(Context context) {
        if (isExternalStorageAvailable()) {
            StatFs stat = new StatFs(Environment.getExternalStorageDirectory().getAbsolutePath());
            long blockSize = stat.getBlockSize();
            long totalBlocks = stat.getBlockCount();
            return Formatter.formatFileSize(context,totalBlocks * blockSize);
        } else {
            return "-1";
        }
    }
}
