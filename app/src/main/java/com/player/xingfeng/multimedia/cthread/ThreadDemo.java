package com.player.xingfeng.multimedia.cthread;

import android.media.MediaSync;

public class ThreadDemo {
    static {
        System.loadLibrary("native-lib");
    }

    public native void normalThread();

    public native void mutexThread();

    public native void callBackFromC();

    private MyErrorListener myErrorListener;
    public void setMyErrorListener(MyErrorListener listener) {
        this.myErrorListener = listener;
    }

    public void onError(int code, String msg) {
        if (myErrorListener != null) {
            myErrorListener.onError(code, msg);
        }

    }


    public interface MyErrorListener {
        void onError(int code, String msg);
    }
}
