#include <jni.h>
#include <string>
#include "queue"
#include "JavaListener.h"
#include <pthread.h>
#include <stdlib.h>

//打印日志
#include <android/log.h>
#include <unistd.h>

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"SHIXING_MEDIA",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"SHIXING_MEDIA",FORMAT,##__VA_ARGS__);

pthread_t produc;
pthread_t custom;
pthread_mutex_t mutex;
pthread_cond_t cond;
std::queue<int> queue;

void *produceCallBack(void *data) {
    while (1)
    {
        pthread_mutex_lock(&mutex);
        queue.push(1);
        LOGI("生产了一个商品 数量 %d",queue.size());
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

        sleep(5);
    }

    pthread_exit(&produc);
}


void *cusstomCallBack(void *data) {
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (queue.size() > 0) {
            queue.pop();
            LOGI("消费了一个商品 数量 %d",queue.size());
        } else {
            LOGI("没有商品可以消费，等待中 %d",queue.size());
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        usleep(1000 * 500);
    }

    pthread_exit(&custom);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_cthread_ThreadDemo_normalThread(JNIEnv *env, jobject instance) {
    LOGI("%s","normalThread called!!");

    //pthread_create(&thread, NULL, normalCallBack, NULL);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_cthread_ThreadDemo_mutexThread(JNIEnv *env, jobject instance) {
    LOGI("%s","mutexThread called!!");

    for (int i = 0;i < 10; i ++) {
        queue.push(i);
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&produc, NULL, produceCallBack, NULL);
    pthread_create(&custom, NULL, cusstomCallBack, NULL);
}


#include "JavaListener.h"
JavaVM *jvm;
JavaListener *javaListener;
pthread_t childThread;


void *callbackFromThread(void *data) {
    JavaListener *javaListener = (JavaListener *)(data);
    javaListener->onError(0, 101, "c++ call java from child thread!!");

    pthread_exit(&childThread);
}



JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void *reserved) {
    JNIEnv *env;
    jvm = vm;

    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    return JNI_VERSION_1_6;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_player_xingfeng_multimedia_cthread_ThreadDemo_callBackFromC(JNIEnv *env, jobject instance) {
    LOGI("%s","callBackFromC called!!");
    javaListener  = new JavaListener(jvm, env, env->NewGlobalRef(instance));
    javaListener->onError(1, 100, "c++ call java from main thread!!");

    pthread_create(&childThread, NULL, callbackFromThread, javaListener);
}
