/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_player_xingfeng_multimedia_Mp3Encoder */
#include <android/log.h>
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_TAG "System.out"

#ifndef _Included_com_player_xingfeng_multimedia_Mp3Encoder
#define _Included_com_player_xingfeng_multimedia_Mp3Encoder
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_player_xingfeng_multimedia_Mp3Encoder
 * Method:    init
 * Signature: (Ljava/lang/String;IIILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_player_xingfeng_multimedia_Mp3Encoder_init
  (JNIEnv *, jobject, jstring, jint, jint, jint, jstring);

/*
 * Class:     com_player_xingfeng_multimedia_Mp3Encoder
 * Method:    encode
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_player_xingfeng_multimedia_Mp3Encoder_encode
  (JNIEnv *, jobject);

/*
 * Class:     com_player_xingfeng_multimedia_Mp3Encoder
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_player_xingfeng_multimedia_Mp3Encoder_destroy
  (JNIEnv *, jobject);
#ifdef __cplusplus
}
#endif
#endif