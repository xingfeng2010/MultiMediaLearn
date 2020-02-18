//
// Created by 李世星 on 2020/2/18.
//

#ifndef MULTIMEDIALEARN_MYLOOPER_H
#define MULTIMEDIALEARN_MYLOOPER_H

#include "Looper.h"
#include "../xingrender/GLRender.h"

enum {
    kMsgSurfaceCreated,
    kMsgSurfaceChanged,
    kMsgSurfaceDestroyed
};

class MyLooper : public Looper {
public:
    MyLooper();
    virtual ~MyLooper();

    virtual void handleMessage(LooperMessage *msg);

private:
    GLRender *mRender;
};

#endif //MULTIMEDIALEARN_MYLOOPER_H
