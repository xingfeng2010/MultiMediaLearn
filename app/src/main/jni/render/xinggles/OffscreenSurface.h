//
// Created by 李世星 on 2020/2/18.
//

#ifndef MULTIMEDIALEARN_OFFSCREENSURFACE_H
#define MULTIMEDIALEARN_OFFSCREENSURFACE_H

#include "EglSurfaceBase.h"

class OffscreenSurface : public EglSurfaceBase {
public:
    OffscreenSurface(EglCore *eglCore, int width, int height);
    void release();
};

#endif //MULTIMEDIALEARN_OFFSCREENSURFACE_H
