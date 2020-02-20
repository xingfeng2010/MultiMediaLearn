//
// Created by 李世星 on 2020/2/18.
//


#include <jni.h>
#include "common/Looper.h"
#include "common/MyLooper.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

MyLooper *myLooper = NULL;
ANativeWindow *mWindow = NULL;

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_NativeRenderActivity_nativeInit(JNIEnv *env, jobject instance) {

    myLooper = new MyLooper();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_NativeRenderActivity_nativeRelease(JNIEnv *env, jobject instance) {

    if (myLooper != NULL) {
        myLooper->quit();
        delete  myLooper;
        myLooper = NULL;
    }

    if (mWindow) {
        ANativeWindow_release(mWindow);
        mWindow = NULL;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_NativeRenderActivity_onSurfaceCreated(JNIEnv *env, jobject instance,
        jobject surface) {

    if (mWindow) {
        ANativeWindow_release(mWindow);
        mWindow = NULL;
    }

    mWindow = ANativeWindow_fromSurface(env, surface);

    if (myLooper != NULL) {
        myLooper->postMessage(kMsgSurfaceCreated, mWindow);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_NativeRenderActivity_onSurfaceChanged(JNIEnv *env, jobject instance,
                                                                          jint width, jint height) {
    if (myLooper) {
        myLooper->postMessage(kMsgSurfaceChanged, width, height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_NativeRenderActivity_onSurfaceDestroyed(JNIEnv *env, jobject instance) {
    if (myLooper) {
        myLooper->postMessage(kMsgSurfaceDestroyed);
    }
}




















