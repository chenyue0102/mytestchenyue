package com.test.testcalendar;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.text.TextPaint;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

import java.util.ArrayList;


/**
 * TODO: document your custom view class.
 */
public class TimeLineView extends View {
    private static final int ITEM_COUNT = 24;       //共计24小时
    private static final int ROUND_MIN = 15;        //分钟规整单位
    private float mItemHeight = 0.f;                //一个条目的高度
    private int mItemTextColor = Color.GRAY;        //条目的文字颜色
    private float mItemTextSize = 0.f;              //条目文字大小
    private int mItemLineColor = Color.GRAY;        //条目横线颜色
    private float mItemLinePaddingLeft = 0.f;       //条目横线左侧偏移，相对于content
    private TextPaint mTextPaint;                   //文字的textPaint
    private Paint mLinePaint;                       //线的Paint

    private float mSchedulePaddingLeft = 0.f;       //日程左侧padding，相对于content
    private int mScheduleBackgroundColor = Color.WHITE;  //日程的背景色
    private Paint mScheduleBackgroundPaint;         //日程背景Paint
    private float mScheduleTextPaddingLeft = 0.f;
    private float mScheduleTextPaddingTop = 0.f;
    private float mScheduleTextPaddingRight = 0.f;
    private float mScheduleTextPaddingBottom = 0.f;
    private int mScheduleTextColor = Color.GRAY;    //日程文字颜色
    private float mScheduleTextSize = 0.f;          //日程文字大小
    private TextPaint mScheduleTextPaint;           //日程文字TextPaint
    //日程
    private class ScheduleInfo{
        int id;             //id，唯一标识
        int startMin;       //开始的分钟数量，如早上6：30 为 6*60+30=390
        int endMin;         //结束的分钟数量
        String text;        //日程文字
    }
    private ArrayList<ScheduleInfo> mSchedules = new ArrayList<>();
    private static final int INVALID_ITEM_ID = -1;
    private int mSelectItemId = INVALID_ITEM_ID;  //选中条目id

    public TimeLineView(Context context) {
        super(context);
        init(null, 0);
    }

    public TimeLineView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(attrs, 0);
    }

    public TimeLineView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        init(attrs, defStyle);
    }

    private void init(AttributeSet attrs, int defStyle) {
        // Load attributes
        final TypedArray a = getContext().obtainStyledAttributes(
                attrs, R.styleable.TimeLineView, defStyle, 0);

        mItemHeight = a.getDimension(R.styleable.TimeLineView_itemHeight, mItemHeight);
        mItemTextColor = a.getColor(R.styleable.TimeLineView_itemTextColor, mItemTextColor);
        mItemTextSize = a.getDimension(R.styleable.TimeLineView_itemTextSize, mItemTextSize);
        mItemLineColor = a.getColor(R.styleable.TimeLineView_itemLineColor, mItemLineColor);
        mItemLinePaddingLeft = a.getDimension(R.styleable.TimeLineView_itemLinePaddingLeft, mItemLinePaddingLeft);

        mSchedulePaddingLeft = a.getDimension(R.styleable.TimeLineView_schedulePaddingLeft, mSchedulePaddingLeft);
        mScheduleBackgroundColor = a.getColor(R.styleable.TimeLineView_scheduleBackgroundColor, mScheduleBackgroundColor);
        mScheduleTextPaddingLeft = a.getDimension(R.styleable.TimeLineView_scheduleTextPaddingLeft, mScheduleTextPaddingLeft);
        mScheduleTextPaddingTop = a.getDimension(R.styleable.TimeLineView_scheduleTextPaddingTop, mScheduleTextPaddingTop);
        mScheduleTextPaddingRight = a.getDimension(R.styleable.TimeLineView_scheduleTextPaddingRight, mScheduleTextPaddingRight);
        mScheduleTextPaddingBottom = a.getDimension(R.styleable.TimeLineView_scheduleTextPaddingBottom, mScheduleTextPaddingBottom);
        mScheduleTextColor = a.getColor(R.styleable.TimeLineView_scheduleTextColor, mScheduleTextColor);
        mScheduleTextSize = a.getDimension(R.styleable.TimeLineView_scheduleTextSize, mScheduleTextSize);

        a.recycle();

        // Set up a default TextPaint object
        mTextPaint = new TextPaint();
        mTextPaint.setFlags(Paint.ANTI_ALIAS_FLAG);
        mTextPaint.setTextAlign(Paint.Align.LEFT);

        mLinePaint = new Paint();

        mScheduleBackgroundPaint = new Paint();
        mScheduleTextPaint = new TextPaint();
        // Update TextPaint and text measurements from attributes
        invalidateTextPaintAndMeasurements();

        setOnLongClickListener(new OnLongClickListener(){
            @Override
            public boolean onLongClick(View v) {
                Rect rect = new Rect();
                v.getLocalVisibleRect(rect);
                int x = rect.centerX();
                int y = rect.centerY();
                ScheduleInfo info = hitTestScheduleInfo(x, y);
                int selectItemId = INVALID_ITEM_ID;
                if (null == info){
                    selectItemId = INVALID_ITEM_ID;
                }else{
                    selectItemId = info.id;
                }
                if (selectItemId != mSelectItemId){
                    mSelectItemId = selectItemId;
                    postInvalidate();
                }
                return false;
            }
        });
    }

    private void invalidateTextPaintAndMeasurements() {
        mTextPaint.setTextSize(mItemTextSize);
        mTextPaint.setColor(mItemTextColor);

        mLinePaint.setColor(mItemLineColor);

        mScheduleBackgroundPaint.setColor(mScheduleBackgroundColor);
        mScheduleTextPaint.setColor(mScheduleTextColor);
        mScheduleTextPaint.setTextSize(mScheduleTextSize);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec){
        int widthMode = MeasureSpec.getMode(widthMeasureSpec);
        int widthSize = MeasureSpec.getSize(widthMeasureSpec);
        int heightMode = MeasureSpec.getMode(heightMeasureSpec);
        int heightSize = MeasureSpec.getSize(heightMeasureSpec);
        switch (heightMode){
            case MeasureSpec.EXACTLY:
                //已经通过layout_height给控件设置宽度
                if (0 == heightSize){
                    heightSize = getMeasureHeight();
                }
                break;
            case MeasureSpec.AT_MOST:
                //wrap_content
                break;
            case MeasureSpec.UNSPECIFIED:
                //未指定
                if (0 == heightSize){
                    heightSize = getMeasureHeight();
                }
                break;
        }
        super.onMeasure(MeasureSpec.makeMeasureSpec(widthSize, widthMode),
                MeasureSpec.makeMeasureSpec(heightSize, heightMode));
    }

    /**
     * 获取适合的高度
     * @return
     */
    int getMeasureHeight(){
        int height = (int)(mItemHeight * ITEM_COUNT);
        height += getPaddingTop() + getPaddingBottom();
        return height;
    }

    private ScheduleInfo getScheduleById(int id){
        ScheduleInfo info = null;
        for (ScheduleInfo tmpInfo : mSchedules){
            if (tmpInfo.id == id){
                info = tmpInfo;
            }
        }
        return info;
    }

    private void sortSchedule(){
        mSchedules.sort((left, right)->{
            if (left.startMin == right.startMin){
                return 0;
            }else if (right.startMin > left.startMin){
                return 1;
            }else{
                return 0;
            }
        });
    }

    public boolean addSchedule(int id, int startMin, int endMin, String text){
        ScheduleInfo info = getScheduleById(id);
        if (null == info){
            info = new ScheduleInfo();
            info.id = id;
            info.startMin = startMin;
            info.endMin = endMin;
            info.text = text;

            mSchedules.add(info);
            sortSchedule();
            postInvalidate();
            return true;
        }else{
            return false;
        }
    }

    public boolean deleteSchedule(int id){
        ScheduleInfo info = getScheduleById(id);
        if (null != info){
            mSchedules.remove(info);
            sortSchedule();
            postInvalidate();
            return true;
        }else{
            return false;
        }
    }

    public void deleteAllSchedule(){
        mSchedules.clear();
        sortSchedule();
        postInvalidate();
    }

    public boolean updateSchedule(int id, int startMin, int endMin, String text){
        ScheduleInfo info = getScheduleById(id);
        if (null != info){
            info.startMin = startMin;
            info.endMin = endMin;
            info.text = text;
            sortSchedule();
            postInvalidate();
            return true;
        }else{
            return false;
        }
    }

//    @Override
//    public boolean onTouchEvent(MotionEvent event){
//        int action = event.getAction();
//        switch (action){
//            case MotionEvent.ACTION_DOWN:
//                break;
//        }
//        return true;
//    }

    ScheduleInfo hitTestScheduleInfo(float x, float y){
        ScheduleInfo resultInfo = null;
        for (ScheduleInfo info : mSchedules){
            RectF rc = getScheduleRectF(info);
            if (rc.contains(x, y)){
                resultInfo = info;
            }
        }
        return resultInfo;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        int paddingLeft = getPaddingLeft();
        int paddingTop = getPaddingTop();
        int paddingRight = getPaddingRight();
        int paddingBottom = getPaddingBottom();

        int contentWidth = getWidth() - paddingLeft - paddingRight;
        int min = 0;
        for (int i  = 0; i < ITEM_COUNT; i++, min += 60){
            canvas.drawText(getTimeText(min), paddingLeft, getTimeTextPositionY(min), mTextPaint);
            float linePositionY = getTimeLinePositionY(min);
            canvas.drawLine(paddingLeft + mItemLinePaddingLeft, linePositionY, paddingLeft + contentWidth, linePositionY, mLinePaint);
        }

        for (ScheduleInfo info : mSchedules){
            drawSchedule(canvas, info, mSelectItemId == info.id);
        }
    }

    private String[] splitText(String text, TextPaint textPaint, float maxWidth){
        float []textWidths = new float[text.length()];
        textPaint.getTextWidths(text, textWidths);
        ArrayList<String> texts = new ArrayList<>();
        float curWidth = 0.f;
        int startIndex = 0;
        for (int i = 0; i < text.length(); i++){
            if (curWidth + textWidths[i] > maxWidth){
                texts.add(text.substring(startIndex, i));
                startIndex = i;
                curWidth = textWidths[i];
            }else {
                curWidth += textWidths[i];
            }
        }
        if (startIndex < text.length()){
            texts.add(text.substring(startIndex, text.length()));
        }
        return texts.toArray(new String[texts.size()]);
    }

    private RectF getScheduleRectF(ScheduleInfo info){
        RectF rc = getContentRectF();
        rc.left += mSchedulePaddingLeft;
        rc.top = getTimeLinePositionY(info.startMin);
        rc.bottom = getTimeLinePositionY(info.endMin);
        return rc;
    }

    private void drawSchedule(Canvas canvas, ScheduleInfo info, boolean isSelected){
        Paint.FontMetrics fontMetrics = mScheduleTextPaint.getFontMetrics();
        RectF rc = getScheduleRectF(info);
        canvas.drawRect(rc, mScheduleBackgroundPaint);

        float offset = (-fontMetrics.ascent) / 2;
        String []texts = splitText(info.text, mScheduleTextPaint, rc.width() - (mScheduleTextPaddingLeft + mScheduleTextPaddingRight));
        for (int i = 0; i < texts.length; i++){
            canvas.drawText(texts[i], rc.left + mScheduleTextPaddingLeft, rc.top + mScheduleTextPaddingTop + (i + 1) * (fontMetrics.bottom - fontMetrics.top) , mScheduleTextPaint);
        }
    }

    /**
     * 获取日期绘制的Y坐标位置
     * @return
     */

    Rect getContentRect(){
        Rect rc = new Rect();
        rc.left = getPaddingLeft();
        rc.top = getPaddingTop();
        rc.right = getWidth() - (getPaddingLeft() + getPaddingRight());
        rc.bottom = getHeight() - (getPaddingTop() + getPaddingBottom());
        return rc;
    }
    RectF getContentRectF(){
        Rect rc = getContentRect();
        return new RectF(rc.left, rc.top, rc.right, rc.bottom);
    }

    int getContentWidth(){
        return getWidth() - getPaddingLeft() - getPaddingRight();
    }

    String getTimeText(int min){
        int hour = min / 60;
        int tmpMin = min % 60;
        return String.format("%02d:%02d", hour, tmpMin);
    }

    /**
     * 获取时间提示文字绘制的Y坐标
     * @param min 第N分钟
     * @return
     */
    float getTimeTextPositionY(int min){
        float position = getTimeLinePositionY(min);
        Paint.FontMetrics fontMetrics = mTextPaint.getFontMetrics();
        float offset = (-fontMetrics.ascent) / 2;
        return position + offset;
    }

    float getTimeLinePositionY(int min){
        float position = (float) getContentRect().height() * ((float)min / (60 * 24));
        return position + getPaddingTop() ;
    }
}
