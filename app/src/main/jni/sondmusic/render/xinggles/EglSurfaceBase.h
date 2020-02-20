//
// Created by 李世星 on 2020/2/18.
//

#ifndef MULTIMEDIALEARN_EGLSURFACEBASE_H
#define MULTIMEDIALEARN_EGLSURFACEBASE_H

#include "egl_core.h"
#include "../../libcommon/native_log.h"

class EglSurfaceBase {
public:
    EglSurfaceBase(EglCore *eglCore);
    //创建窗口Surface
    void createWindoSurface(ANativeWindow *nativeWindow);
    //创建离屏Surface
    void createOffscreenSurface(int width, int height);
    // 获取宽度
    int getWidth();
    // 获取高度
    int getHeight();
    // 释放EGLSurface
    void releaseEglSurface();
    // 切换到当前上下文
    void makeCurrent();
    // 交换缓冲区
    bool swapBuffers();
    // 设置显示时间戳
    void setPresentationTime(long nsecs);
    // 获取当前帧缓冲
    char *getCurrentFrame();

protected:
    EglCore *mEglCore;
    EGLSurface mEglSurface;
    int mWidth;
    int mHeight;

};

#endif //MULTIMEDIALEARN_EGLSURFACEBASE_H
