package com.player.xingfeng.multimedia;

import android.Manifest;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    public String LOG_TAG = "System.out";

    Mp3Encoder encoder;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        checkPermission();

        String pcmPath = "/sdcard/16k.pcm";
        int audioChannels = 1;
        int bitRate = 16;
        int sampleRate = 16 * 1000;
        String mp3Path = "/sdcard/convertpcm.mp3";

        encoder = new Mp3Encoder();
        Log.i(LOG_TAG,"onCreate !!!");
        encoder.init(pcmPath, audioChannels, bitRate, sampleRate, mp3Path);
        Log.i(LOG_TAG,"onCreate init success!!");
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
