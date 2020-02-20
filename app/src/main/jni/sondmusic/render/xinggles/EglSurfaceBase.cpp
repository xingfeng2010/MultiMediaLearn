//
// Created by 李世星 on 2020/2/18.
//

#include <assert.h>
#include <GLES2/gl2.h>
#include "EglSurfaceBase.h"

EglSurfaceBase::EglSurfaceBase(EglCore *eglCore) : mEglCore(eglCore) {
    mEglSurface = EGL_NO_SURFACE;
}

/**
 * 创建显示的Surface
 * @param nativeWindow
 */
void EglSurfaceBase::createWindoSurface(ANativeWindow *nativeWindow) {
    if (mEglSurface != EGL_NO_SURFACE) {
        ALOGE("surface already created\n");
        return;
    }
    mEglSurface = mEglCore->createWindowSurface(nativeWindow);
}

/**
 * 创建离屏surface
 * @param width
 * @param height
 */
void EglSurfaceBase::createOffscreenSurface(int width, int height) {
    if (mEglSurface != EGL_NO_SURFACE) {
        ALOGE("surface already created\n");
        return;
    }

    mEglSurface = mEglCore->createOffscreenSurface(width, height);
    mWidth = width;
    mHeight = height;
}

int EglSurfaceBase::getWidth() {
    if (mWidth < 0) {
        return mEglCore->querySurface(mEglSurface, EGL_WIDTH);
    } else {
        return mWidth;
    }
}

int EglSurfaceBase::getHeight() {
    if (mHeight < 0) {
        return mEglCore->querySurface(mEglSurface, EGL_HEIGHT);
    } else {
        return mHeight;
    }
}

void EglSurfaceBase::releaseEglSurface() {
    mEglCore->releaseSurface(mEglSurface);
    mEglSurface = EGL_NO_SURFACE;
    mWidth = mHeight = -1;
}

/**
 * 切换到当前EGLContext
 */
void EglSurfaceBase::makeCurrent() {
    mEglCore->makeCurrent(mEglSurface);
}

/**
 * 交换到前台显示
 * @return
 */
bool EglSurfaceBase::swapBuffers() {
    bool result = mEglCore->swapBuffers(mEglSurface);
    if (!result) {
        ALOGD("WARNING: swapBuffers() failed");
    }

    return result;
}

/**
 * 设置当前时间戳
 * @param nsecs
 */
void EglSurfaceBase::setPresentationTime(long nsecs) {
    mEglCore->setPresentationTime(mEglSurface, nsecs);
}

char* EglSurfaceBase::getCurrentFrame() {
    char *pixels = NULL;
    glReadPixels(0, 0, getWidth(), getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    return pixels;
}

