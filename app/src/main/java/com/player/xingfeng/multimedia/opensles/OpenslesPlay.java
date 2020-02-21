package com.player.xingfeng.multimedia.opensles;

import android.content.res.AssetManager;

public class OpenslesPlay {

    public native void playAudioByOpenSL_assets(AssetManager assetManager, String filename);

    public native void playAudioByOpenSL_uri(String uri);

    public native void playAudioByOpenSL_pcm(String pamPath);



    /**
     *
     * java层提供pcm数据，opensl底层播放
     *
     * 只是演示播放方式，停止回收资源逻辑自行设计
     *
     * @param data
     * @param size
     */
    public native void sendPcmData(byte[] data, int size);
}
