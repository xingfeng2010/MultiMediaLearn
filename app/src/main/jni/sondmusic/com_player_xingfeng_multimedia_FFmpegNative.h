/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <stdio.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_TAG "System.out"

/* Header for class com_player_xingfeng_multimedia_FFmpegNative */

//Log
#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "(>_<)", format, ##__VA_ARGS__)
#else
#define LOGE(format, ...)  printf("(>_<) " format "\n", ##__VA_ARGS__)
#endif

#ifndef _Included_com_player_xingfeng_multimedia_FFmpegNative
#define _Included_com_player_xingfeng_multimedia_FFmpegNative
#ifdef __cplusplus
extern "C" {
#include "ffmpeg/include/libavcodec/avcodec.h"
#include "ffmpeg/include/libavformat/avformat.h"
#include "ffmpeg/include/libavfilter/avfilter.h"
#include "ffmpeg/include/libavutil/avutil.h"
#include "ffmpeg/include/libavutil/frame.h"
#include "ffmpeg/include/libavutil/imgutils.h"
#include "ffmpeg/include/libavutil/time.h"
#include "ffmpeg/include/libavutil/mathematics.h"
#include "platform_4_ffmpeg.h"

//-----AVfilter-----
#include "ffmpeg/include/libavfilter/avfiltergraph.h"
#include "ffmpeg/include/libavfilter/buffersrc.h"
#include "ffmpeg/include/libavfilter/buffersink.h"
//-----AVfilter-----

int avError(int errNum) {
    char buf[1024];
    //获取错误信息
    av_strerror(errNum, buf, sizeof(buf));
    //LOGE("发生异常：" + buf + c_str());
    return -1;
}

#endif
/*
 * Class:     com_player_xingfeng_multimedia_FFmpegNative
 * Method:    urlprotocolinfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_player_xingfeng_multimedia_FFmpegNative_urlprotocolinfo
  (JNIEnv *env, jobject obj);

/*
 * Class:     com_player_xingfeng_multimedia_FFmpegNative
 * Method:    avformatinfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_player_xingfeng_multimedia_FFmpegNative_avformatinfo
  (JNIEnv *, jobject);

/*
 * Class:     com_player_xingfeng_multimedia_FFmpegNative
 * Method:    avcodecinfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_player_xingfeng_multimedia_FFmpegNative_avcodecinfo
  (JNIEnv *, jobject);

/*
 * Class:     com_player_xingfeng_multimedia_FFmpegNative
 * Method:    avfilterinfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_player_xingfeng_multimedia_FFmpegNative_avfilterinfo
  (JNIEnv *, jobject);

/*
 * Class:     com_player_xingfeng_multimedia_FFmpegNative
 * Method:    configurationinfo
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_player_xingfeng_multimedia_FFmpegNative_configurationinfo
  (JNIEnv *, jobject);

JNIEXPORT jint JNICALL
Java_com_player_xingfeng_multimedia_FFmpegNative_decode(JNIEnv *env, jobject instance, jstring inputPath, jstring outputPath);

JNIEXPORT jint JNICALL
Java_com_player_xingfeng_multimedia_FFmpegNative_pushStream(JNIEnv *env, jobject instance,
                                                            jstring inputPath_, jstring playUrl_);

JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_FFmpegNative_play(JNIEnv *env, jobject instance,
                                                            jstring url, jobject surface);
#ifdef __cplusplus
}
#endif
#endif
