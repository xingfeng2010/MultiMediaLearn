package com.player.xingfeng.multimedia;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class NativeRenderActivity extends AppCompatActivity implements SurfaceHolder.Callback{

    private native void nativeInit();
    private native void nativeRelease();
    private native void onSurfaceCreated(Surface surface);
    private native void onSurfaceChanged(int width, int height);
    private native void onSurfaceDestroyed();

    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("audioencoder");
    }

    private SurfaceView mSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_native_render);

        nativeInit();
        mSurfaceView = (SurfaceView) findViewById(R.id.surface_view);
        mSurfaceView.getHolder().addCallback(this);
    }

    @Override
    protected void onDestroy() {
        nativeRelease();
        super.onDestroy();
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        onSurfaceCreated(surfaceHolder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int format, int width, int height) {
        onSurfaceChanged(width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        onSurfaceDestroyed();
    }
}
