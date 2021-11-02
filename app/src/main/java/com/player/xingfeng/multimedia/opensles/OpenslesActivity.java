package com.player.xingfeng.multimedia.opensles;

import android.content.res.AssetManager;
import android.os.Environment;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.player.xingfeng.multimedia.R;

import java.io.FileInputStream;
import java.io.InputStream;

import androidx.appcompat.app.AppCompatActivity;

public class OpenslesActivity extends AppCompatActivity {

    static {
        System.loadLibrary("openslaudio");
    }

    AssetManager assetManager;
    private OpenslesPlay mOpenslesPlay;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opensles);
        assetManager = getAssets();

        mOpenslesPlay = new OpenslesPlay();
    }


    public void play_assets(View view) {
        mOpenslesPlay.playAudioByOpenSL_assets(assetManager, "background.mp3");
    }


    public void play_uri(View view) {
        mOpenslesPlay.playAudioByOpenSL_uri("http://mpge.5nd.com/2015/2015-11-26/69708/1.mp3");
    }

    public void play_pcm(View view) {

        String path = Environment.getExternalStorageDirectory().getAbsolutePath() + "/mydream.pcm";
        Log.d("ywl5320", path);
        mOpenslesPlay.playAudioByOpenSL_pcm("/mnt/sdcard/mydream.pcm");
    }

    boolean isstart = false;

    public void play_javapcm(View view) {

        if(!isstart)
        {
            isstart = true;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        InputStream in = new FileInputStream("/mnt/sdcard/mydream.pcm");
                        byte[] buffer = new byte[44100 * 2 * 2];
                        int n = 0;
                        while((n = in.read(buffer)) != -1)
                        {
                            mOpenslesPlay.sendPcmData(buffer, n);
                            Thread.sleep(800);
                        }
                        isstart = false;
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }).start();
        }


    }
}
