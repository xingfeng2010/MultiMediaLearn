package com.player.xingfeng.multimedia;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class FFMpegFilterActivity extends AppCompatActivity implements SurfaceHolder.Callback{
    FFmpegNative fFmpegNative;
    SurfaceView surfaceView;
    public String videoPath = "http://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4";

    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("audioencoder");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ffmpeg_filter);

        surfaceView = (SurfaceView)this.findViewById(R.id.surface_view);
        surfaceView.getHolder().addCallback(this);

        fFmpegNative = new FFmpegNative();
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        final Surface surface =  surfaceHolder.getSurface();
        new Thread() {


            @Override
            public void run() {
                fFmpegNative.play(videoPath, surface);
            }
        }.start();

    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }
}
