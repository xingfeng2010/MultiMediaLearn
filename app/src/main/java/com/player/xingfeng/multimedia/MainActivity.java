package com.player.xingfeng.multimedia;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

public class MainActivity extends AppCompatActivity {

    public static final String LOG_TAG = "System.out";

    Mp3Encoder encoder;
    FFmpegNative fFmpegNative;

    private TextView mmText;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("audioencoder");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mmText = (TextView) findViewById(R.id.mmText);
        mmText.setMovementMethod(ScrollingMovementMethod.getInstance());

//        // Example of a call to a native method
//        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(stringFromJNI());

        checkPermission();

        // testLame();
        //testFFmpeg();
    }


    public void showFFMpegInfo(View view) {
        switch (view.getId()) {
            case R.id.Protocol:
                //mmText.setText(fFmpegNative.urlprotocolinfo());
                pushStream();
                break;
            case R.id.Format:
                mmText.setText(fFmpegNative.avformatinfo());
                break;
            case R.id.Codec:
                mmText.setText(fFmpegNative.avcodecinfo());
                break;
            case R.id.Filter:
                mmText.setText(fFmpegNative.avfilterinfo());
                break;
            case R.id.Configuration:
                mmText.setText(fFmpegNative.configurationinfo());
                break;
        }
    }

    private void testFFmpeg() {
        String inputPath = "/sdcard/testffmpeg.mp4";
        String outputPath = "/sdcard/testffmpeg.yuv";

        fFmpegNative = new FFmpegNative();
        fFmpegNative.decode(inputPath, outputPath);
    }

    private void pushStream() {
        new Thread() {
            @Override
            public void run() {
                String inputPath = "/sdcard/testffmpeg.flv";
                String outputPath = "rtmp://192.168.43.24/rtmplive/room";

                fFmpegNative = new FFmpegNative();
                int pushResult =  fFmpegNative.pushStream(inputPath, outputPath);

                Log.i(LOG_TAG, "pushResult:" + pushResult);
            }
        }.start();
    }

    private void testLame() {
        String pcmPath = "/sdcard/16k.pcm";
        int audioChannels = 1;
        int bitRate = 16;
        int sampleRate = 16 * 1000;
        String mp3Path = "/sdcard/convertpcm.mp3";

        encoder = new Mp3Encoder();
        Log.i(LOG_TAG, "onCreate !!!");
        encoder.init(pcmPath, audioChannels, bitRate, sampleRate, mp3Path);
        Log.i(LOG_TAG, "onCreate init success!!");
        encoder.encode();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        //   encoder.destroy();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    private void checkPermission() {
        //检查权限（NEED_PERMISSION）是否被授权 PackageManager.PERMISSION_GRANTED表示同意授权
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            //用户已经拒绝过一次，再次弹出权限申请对话框需要给用户一个解释
            if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission
                    .WRITE_EXTERNAL_STORAGE)) {
                Toast.makeText(this, "请开通相关权限，否则无法正常使用本应用！", Toast.LENGTH_SHORT).show();
            }
            //申请权限
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 12);

        } else {
            Toast.makeText(this, "授权成功！", Toast.LENGTH_SHORT).show();
        }
    }
}
