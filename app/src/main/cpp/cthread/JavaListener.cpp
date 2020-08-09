//
// Created by 李世星 on 2020-08-09.
//

#include "JavaListener.h"

JavaListener::JavaListener(JavaVM *vm, _JNIEnv *env, jobject obj) {
    jvm = vm;
    jniEnv = env;
    jobj = obj;

    jclass clz = env->GetObjectClass(obj);
    if (!clz)
    {
        return ;
    }

    jmid = env->GetMethodID(clz, "onError","(ILjava/lang/String;)V");
}

void JavaListener::onError(int threadType, int code, const char *msg) {
    if (threadType == 0)
    {//子主线程


        JNIEnv *env;
        jvm->AttachCurrentThread(&env, 0);

        jstring jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj, jmid, code, jmsg);
        env->DeleteLocalRef(jmsg);

        jvm->DetachCurrentThread();
    }
    else if (threadType == 1)
    {//主线程
        jstring jmsg = jniEnv->NewStringUTF(msg);
        jniEnv->CallVoidMethod(jobj, jmid, code, jmsg);
        jniEnv->DeleteLocalRef(jmsg);
    }
}
