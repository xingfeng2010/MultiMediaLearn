//
// Created by 李世星 on 2020/2/18.
//

#ifndef MULTIMEDIALEARN_GLRENDER_H
#define MULTIMEDIALEARN_GLRENDER_H

#include <android/native_window.h>
#include "../xinggles/egl_core.h"
#include "../xinggles/WindowSurface.h"
#include "Triangle.h"

class GLRender {
public:
    GLRender();

    virtual ~GLRender();

    void surfaceCreated(ANativeWindow *window);

    void surfaceChanged(int width, int height);

    void surfaceDestroyed(void);

private:
    EglCore *mEglCore;
    WindowSurface *mWindowSurface;
    Triangle *mTriangle;
};

#endif //MULTIMEDIALEARN_GLRENDER_H
