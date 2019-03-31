package com.player.xingfeng.multimedia;

public class Mp3Encoder {
    static {
        System.loadLibrary("audioencoder");
    }

    public native void encode();
}
