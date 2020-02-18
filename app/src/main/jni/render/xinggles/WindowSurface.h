//
// Created by 李世星 on 2020/2/18.
//

#ifndef MULTIMEDIALEARN_WINDOWSURFACE_H
#define MULTIMEDIALEARN_WINDOWSURFACE_H

#include "EglSurfaceBase.h"

class WindowSurface : public EglSurfaceBase {
public:
    WindowSurface(EglCore *eglCore, ANativeWindow *window, bool releaseSurface);
    WindowSurface(EglCore *eglCore, ANativeWindow *window);

    //释放资源
    void release();
    //重新创建
    void recreate(EglCore *eglCore);

private:
    ANativeWindow *mSurface;
    bool mReleaseSurface;
};

#endif //MULTIMEDIALEARN_WINDOWSURFACE_H
