package com.player.xingfeng.multimedia.audioplay;

import android.os.Handler;
import android.os.Message;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.player.xingfeng.multimedia.R;
import com.player.xingfeng.multimedia.audioplay.audiotrack.NativeMp3PlayerController;
import com.player.xingfeng.multimedia.audioplay.opensles.SoundTrackController;

import androidx.appcompat.app.AppCompatActivity;


public class AudioPlayActivity extends AppCompatActivity {
    private static final String TAG = "AudioPlayActivity";
    static {
        System.loadLibrary("audioencoder");
        System.loadLibrary("musicdecoder");
    }

    /** 要播放的文件路径 **/
    private static String playFilePath = "/mnt/sdcard/131.mp3";

    private SoundTrackController soundTrackController;
    private NativeMp3PlayerController audioTrackPlayerController;

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

    public void audioPlay(View view) {
        audioTrackPlayerController = new NativeMp3PlayerController();
        audioTrackPlayerController.setHandler(handler);
        audioTrackPlayerController.setAudioDataSource(playFilePath);
        audioTrackPlayerController.start();
    }

    public void audioStop(View view) {
        if (null != audioTrackPlayerController) {
            audioTrackPlayerController.stop();
            audioTrackPlayerController = null;
        }
    }

    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            // 计算当前时间
            int _time = Math.max(msg.arg1, 0) / 1000;
            int total_time = Math.max(msg.arg2, 0) / 1000;
            float ratio = (float) _time / (float) total_time;
            Log.i(TAG, "Play Progress : " + ratio);
        }
    };
}
