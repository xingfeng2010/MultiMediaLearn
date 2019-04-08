package com.player.xingfeng.multimedia;

public class FFmpegNative {
    public native String urlprotocolinfo();
    public native String avformatinfo();
    public native String avcodecinfo();
    public native String avfilterinfo();
    public native String configurationinfo();

    public native int decode(String inputPath, String outputPath);

    public native int pushStream(String inputPath, String playUrl);
}
