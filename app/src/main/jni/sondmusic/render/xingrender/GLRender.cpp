//
// Created by 李世星 on 2020/2/18.
//

#include "GLRender.h"
#include "../xinggles/GlUtils.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

GLRender::GLRender() {
    mEglCore = NULL;
    mWindowSurface = NULL;
}

GLRender::~GLRender() {
    if (mEglCore) {
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }
}

void GLRender::surfaceCreated(ANativeWindow *window) {
    if (mEglCore == NULL) {
        mEglCore = new EglCore(NULL, FLAG_RECORDABLE);
    }

    mWindowSurface = new WindowSurface(mEglCore, window, false);
    mWindowSurface->makeCurrent();
    mTriangle = new Triangle();
    mTriangle->init();
}

void GLRender::surfaceChanged(int width, int height) {
    mWindowSurface->makeCurrent();
    mTriangle->onDraw(width, height);
    mWindowSurface->swapBuffers();
}

void GLRender::surfaceDestroyed() {
    if (mTriangle) {
        mTriangle->destroy();
        delete mTriangle;
        mTriangle = NULL;
    }

    if (mWindowSurface) {
        mWindowSurface->release();
        delete mWindowSurface;
        mWindowSurface = NULL;
    }

    if (mEglCore) {
        mEglCore->release();
        delete mEglCore;
        mEglCore = NULL;
    }
}
