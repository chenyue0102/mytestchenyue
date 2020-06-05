package com.test.testcalendar;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;

import com.haibin.calendarview.CalendarLayout;
import com.haibin.calendarview.CalendarView;

public class MainActivity extends AppCompatActivity {
    CalendarView calendarView = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        calendarView = findViewById(R.id.calendarView);
        CalendarLayout calendarLayout = findViewById(R.id.calendarLayout);

        Button btnExpend = findViewById(R.id.btn_expand);
        btnExpend.setOnClickListener((view)->{
            calendarLayout.expand();
        });

        Button btnShrink = findViewById(R.id.btn_shrink);
        btnShrink.setOnClickListener((view)->{
            calendarLayout.shrink();
        });

        TimeLineView timeLineView = findViewById(R.id.timeLineView);
        timeLineView.addSchedule(1, 45, 90, "一二三四五六七八九十一二三四五六七八九十一二三四五六七八九十一二三四五六七八九十");
    }
}
