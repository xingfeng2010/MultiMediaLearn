//
// Created by 李世星 on 2020/2/18.
//

#include "WindowSurface.h"

WindowSurface::WindowSurface(EglCore *eglCore, ANativeWindow *window, bool releaseSurface)
        : EglSurfaceBase(eglCore) {
    mSurface = window;
    createWindoSurface(mSurface);
    mReleaseSurface = releaseSurface;
}

WindowSurface::WindowSurface(EglCore *eglCore, ANativeWindow *window)
    : EglSurfaceBase(eglCore) {
    createWindoSurface(window);
    mSurface = window;
}

void WindowSurface::release() {
    releaseEglSurface();
    if (mSurface != NULL) {
        ANativeWindow_release(mSurface);
        mSurface = NULL;
    }
}

void WindowSurface::recreate(EglCore *eglCore) {
    if (mSurface == NULL) {
        ALOGE("not yet implemented ANativeWindow");
        return;
    }
    mEglCore = eglCore;
    createWindoSurface(mSurface);
}
