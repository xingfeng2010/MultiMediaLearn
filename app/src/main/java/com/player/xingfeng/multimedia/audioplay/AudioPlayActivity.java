package com.player.xingfeng.multimedia.audioplay;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.player.xingfeng.multimedia.R;
import com.player.xingfeng.multimedia.audioplay.opensles.SoundTrackController;

public class AudioPlayActivity extends AppCompatActivity {
    static {
        System.loadLibrary("audioencoder");
    }

    /** 要播放的文件路径 **/
    private static String playFilePath = "/mnt/sdcard/131.mp3";

    private SoundTrackController soundTrackController;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_play2);
    }

    public void openslPlay(View view) {
        soundTrackController = new SoundTrackController();
        boolean result = soundTrackController.setAudioDataSource(playFilePath, 0.2f);
        if (result) {
            Log.i("Shixing_ffmpeg", "setAudioDataSource 成功");
        } else {
            Log.i("Shixing_ffmpeg", "setAudioDataSource 失败");
        }

        soundTrackController.play();
    }

    public void openslStop(View view) {
        soundTrackController.stop();
        soundTrackController = null;
    }
}
