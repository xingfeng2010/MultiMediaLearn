package com.player.xingfeng.multimedia;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

public class LivePushActivity extends AppCompatActivity {

    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("audioencoder");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_live_push);

        checkPermission();
    }


    public void startPush(View view) {
        new Thread() {
            @Override
            public void run() {
                String inputPath = "/sdcard/testffmpeg.flv";
                String outputPath = "rtmp://192.168.43.24/rtmplive/room";

                FFmpegNative fFmpegNative = new FFmpegNative();
                int pushResult =  fFmpegNative.pushStream(inputPath, outputPath);

                Log.i(MainActivity.LOG_TAG, "pushResult:" + pushResult);
            }
        }.start();
    }

    private void checkPermission() {
        //检查权限（NEED_PERMISSION）是否被授权 PackageManager.PERMISSION_GRANTED表示同意授权
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA)
                != PackageManager.PERMISSION_GRANTED) {
            //用户已经拒绝过一次，再次弹出权限申请对话框需要给用户一个解释
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission
                    .CAMERA)) {
                Toast.makeText(this, "请开通相关权限，否则无法正常使用本应用！", Toast.LENGTH_SHORT).show();
            }
            //申请权限
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA}, 12);

        } else {
            Toast.makeText(this, "授权成功！", Toast.LENGTH_SHORT).show();
        }
    }
}
