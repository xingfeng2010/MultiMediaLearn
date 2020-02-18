//
// Created by 李世星 on 2020/2/18.
//

#include "OffscreenSurface.h"

OffscreenSurface::OffscreenSurface(EglCore *eglCore, int width, int height)
        : EglSurfaceBase(eglCore) {
    createOffscreenSurface(width, height);
}

void OffscreenSurface::release() {
    releaseEglSurface();
}