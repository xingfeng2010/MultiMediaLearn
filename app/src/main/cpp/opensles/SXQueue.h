//
// Created by 李世星 on 2020/2/21.
//

#ifndef MULTIMEDIALEARN_SXQUEUE_H
#define MULTIMEDIALEARN_SXQUEUE_H

#include <queue>
#include "pcmdata.h"
#include <pthread.h>

class SXQueue {

public:
    std::queue<pcmdata*> queuePacket;
    pthread_mutex_t mutexPacket;
    pthread_cond_t condPacket;

public:
    SXQueue();
    ~SXQueue();
    int putPcmdata(pcmdata *data);
    pcmdata* getPcmdata();
    int clearPcmdata();

    void release();
    int getPcmdataSize();

    int noticeThread();
};


#endif //MULTIMEDIALEARN_SXQUEUE_H
