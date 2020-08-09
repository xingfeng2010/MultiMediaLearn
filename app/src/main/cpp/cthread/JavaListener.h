//
// Created by 李世星 on 2020-08-09.
//

#include "jni.h"
#include "../../../../../../../../../../Library/Android/sdk/android-ndk-r20b/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"

#ifndef MULTIMEDIALEARN_JAVALISTENER_H
#define MULTIMEDIALEARN_JAVALISTENER_H

class JavaListener {

public:
    JavaVM *jvm;
    _JNIEnv *jniEnv;
    jobject jobj;

    jmethodID jmid;

public:
    JavaListener(JavaVM *vm, _JNIEnv *jniEnv, jobject obj);
    ~JavaListener();
    /**
     *
     * @param threadType
     * @param code
     * @param msg
     */
    void onError(int threadType, int code, const char *msg);

};


#endif //MULTIMEDIALEARN_JAVALISTENER_H
