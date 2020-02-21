//
// Created by 李世星 on 2020/2/21.
//

#include <malloc.h>
#include "SXQueue.h"

SXQueue::SXQueue() {
    pthread_mutex_init(&mutexPacket, NULL);
    pthread_cond_init(&condPacket, NULL);
}

SXQueue::~SXQueue() {
    pthread_mutex_destroy(&mutexPacket);
    pthread_cond_destroy(&condPacket);
}

void SXQueue::release() {
    noticeThread();
    clearPcmdata();
}

int SXQueue::putPcmdata(pcmdata *data){

    pthread_mutex_lock(&mutexPacket);
    queuePacket.push(data);
    pthread_cond_signal(&condPacket);
    pthread_mutex_unlock(&mutexPacket);

    return 0;
}

pcmdata* SXQueue::getPcmdata(){

    pthread_mutex_lock(&mutexPacket);
    pcmdata *pkt = NULL;
    if(queuePacket.size() > 0)
    {
        pkt = queuePacket.front();
        queuePacket.pop();
    } else{
        pthread_cond_wait(&condPacket, &mutexPacket);
    }
    pthread_mutex_unlock(&mutexPacket);
    return pkt;
}

int SXQueue::clearPcmdata() {

    pthread_cond_signal(&condPacket);
    pthread_mutex_lock(&mutexPacket);
    while (!queuePacket.empty())
    {
        pcmdata *pkt = queuePacket.front();
        queuePacket.pop();
        free(pkt->getData());
        pkt = NULL;
    }
    pthread_mutex_unlock(&mutexPacket);
    return 0;
}

int SXQueue::getPcmdataSize() {
    int size = 0;
    pthread_mutex_lock(&mutexPacket);
    size = queuePacket.size();
    pthread_mutex_unlock(&mutexPacket);
    return size;
}

int SXQueue::noticeThread() {
    pthread_cond_signal(&condPacket);
    return 0;
}
