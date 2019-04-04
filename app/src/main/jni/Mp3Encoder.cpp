//
// Created by 李世星 on 2019/3/31.
//
#include "com_player_xingfeng_multimedia_Mp3Encoder.h"
#include "mp3_encoder.h"

Mp3Encoder* encoder;

JNIEXPORT void JNICALL Java_com_player_xingfeng_multimedia_Mp3Encoder_encode(JNIEnv *, jobject) {
    LOGI("My Audio Encoder!!!");
    encoder->Encode();
}

JNIEXPORT jint JNICALL Java_com_player_xingfeng_multimedia_Mp3Encoder_init
        (JNIEnv *env, jobject obj, jstring pcmPathParam, jint audioChannels, jint bitRate, jint sampleRate, jstring mp3PathParam) {
    const char * pcmPath = env->GetStringUTFChars(pcmPathParam, NULL);
    const char * mp3Path = env->GetStringUTFChars(mp3PathParam, NULL);
    encoder = new Mp3Encoder();
    encoder->Init(pcmPath,mp3Path,sampleRate, audioChannels, bitRate);
    env->ReleaseStringUTFChars(pcmPathParam, pcmPath);
    env->ReleaseStringUTFChars(mp3PathParam, mp3Path);
}

JNIEXPORT void JNICALL Java_com_player_xingfeng_multimedia_Mp3Encoder_destroy
        (JNIEnv *, jobject) {
    encoder->Destroy();
}