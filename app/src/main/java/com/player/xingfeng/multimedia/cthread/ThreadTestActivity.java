package com.player.xingfeng.multimedia.cthread;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.player.xingfeng.multimedia.R;

import androidx.appcompat.app.AppCompatActivity;

public class ThreadTestActivity extends AppCompatActivity {
     ThreadDemo mThreadDemo;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread_test);

        mThreadDemo = new ThreadDemo();
        mThreadDemo.setMyErrorListener(new ThreadDemo.MyErrorListener() {
            @Override
            public void onError(int code, String msg) {
                Log.i("SHIXING_MEDIA", " code :" + code + " msg:" + msg);
            }
        });
    }


    public void startNormalThread(View view) {
        mThreadDemo.normalThread();
    }

    public void startMutextThread(View view) {
        mThreadDemo.mutexThread();
    }

    public void callBackFromC(View view) {
        mThreadDemo.callBackFromC();
    }
}
