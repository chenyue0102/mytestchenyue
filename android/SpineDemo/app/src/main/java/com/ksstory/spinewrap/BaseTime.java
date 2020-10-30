package com.ksstory.spinewrap;

import android.os.SystemClock;

/**
 * 本地无关的时间计算类
 */
public class BaseTime {
    public BaseTime(){
        setBaseTimeUs(0);
    }

    //设置UTC基准时间，单位秒
    public void setBaseTime(long baseTime){
        setBaseTimeMs(baseTime * 1000);
    }

    //设置UTC基准时间，单位毫秒
    public void setBaseTimeMs(long baseTimeMs){
        setBaseTimeUs(baseTimeMs * 1000);
    }

    //设置UTC基准时间，单位微秒
    public void setBaseTimeUs(long baseTimeUs){
        mBaseTimeUs = baseTimeUs;
        mTimePoint = SystemClock.elapsedRealtimeNanos() / 1000;
    }

    //获取UTC基准时间，单位秒
    public long getCurrentTime(){
        return getCurrentTimeMs() / 1000;
    }

    //获取UTC基准时间，单位毫秒
    public long getCurrentTimeMs(){
        return getCurrentTimeUs() / 1000;
    }

    //获取UTC基准时间，单位微秒
    public long getCurrentTimeUs(){
        long diff = SystemClock.elapsedRealtimeNanos() - mTimePoint;
        long diffUs = diff / 1000;
        return mBaseTimeUs + diffUs;
    }

    private long mTimePoint;
    private long mBaseTimeUs;
}
