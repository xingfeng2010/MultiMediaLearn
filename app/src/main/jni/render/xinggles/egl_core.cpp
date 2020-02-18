//
// Created by 李世星 on 2020/2/17.
//
#include "../common/native_log.h"
#include "egl_core.h"
#include <assert.h>



EglCore::EglCore() {
    init(NULL, 0);
}


EglCore::~EglCore() {
    release();
}


EglCore::EglCore(EGLContext sharedContext, int flags) {
    init(sharedContext, flags);
}

bool EglCore::init(EGLContext sharedContext, int flags) {
    assert(mEGLDisplay == EGL_NO_DISPLAY);
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        ALOGE("EGL already set up");
        return false;
    }
    if (sharedContext == NULL) {
        sharedContext == EGL_NO_CONTEXT;
    }

    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    assert(mEGLDisplay != EGL_NO_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        ALOGE("unable to get EGL14 display.\n");
        return false;
    }

    // 尝试使用GLES3
    if ((flags & FLAG_TRY_GLES3) != 0) {
        EGLConfig  config = getConfig(flags, 3);
        if (config != NULL) {
            int attrib3_list[] = {
                    EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE
            };
            EGLContext context = eglCreateContext(mEGLDisplay, config, sharedContext, attrib3_list);
            checkEglError("eglCreateContext");
            if (eglGetError() == EGL_SUCCESS) {
                mEGLConfig = config;
                mEGLContext = context;
                mGlVersion = 3;
            }
        }
    }

    // 如果GLES3没有获取到，则尝试使用GLES2
    if (mEGLContext == EGL_NO_CONTEXT) {
        EGLConfig  config = getConfig(flags, 2);
        assert(config != NULL);
        int attrib2_list[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
        };

        EGLContext context = eglCreateContext(mEGLDisplay, config, sharedContext, attrib2_list);
        checkEglError("eglCreateContext");
        if (eglGetError() == EGL_SUCCESS) {
            mEGLConfig = config;
            mEGLContext = context;
            mGlVersion = 2;
        }
    }

    // 获取eglPresentationTimeANDROID方法的地址
    eglPresentationTimeANDROID = (EGL_PRESENTATION_TIME_ANDROIDPROC)eglGetProcAddress("eglPresentationTimeANDROID");
    if (!eglPresentationTimeANDROID) {
        ALOGE("eglPresentationTimeANDROID is not available!");
    }

    int values[1] = {0};
    eglQueryContext(mEGLDisplay, mEGLContext, EGL_CONTEXT_CLIENT_VERSION, values);
    ALOGD("EGLContext created, client version %d", values[0]);

    return true;
}

/**
 * 获取合适的EGLConfig
 * @param flags
 * @param version
 * @return
 */
EGLConfig EglCore::getConfig(int flags, int version) {
    int renderableType = EGL_OPENGL_ES2_BIT;
    if (version >= 3) {
        renderableType |= EGL_OPENGL_ES3_BIT_KHR;
    }

    int attribList[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            //EGL_DEPTH_SIZE, 16,
            //EGL_STENCIL_SIZE, 8,
            EGL_RENDERABLE_TYPE, renderableType,
            EGL_NONE, 0,      // placeholder for recordable [@-3]
            EGL_NONE
    };
    int length = sizeof(attribList) / sizeof(attribList[0]);
    if ((flags & FLAG_RECORDABLE) != 0) {
        attribList[length - 3] = EGL_RECORDABLE_ANDROID;
        attribList[length - 2] = 1;
    }

    EGLConfig  configs = NULL;
    int numConfigs;
    if (!eglChooseConfig(mEGLDisplay, attribList, &configs, 1, &numConfigs)) {
        ALOGW("unable to find RGB8888 / %d EGLConfig", version);
        return NULL;
    }

    return configs;
}

// 释放资源
void EglCore::release() {
    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroyContext(mEGLDisplay, mEGLContext);
        eglReleaseThread();
        eglTerminate(mEGLDisplay);
    }

    mEGLDisplay = EGL_NO_DISPLAY;
    mEGLContext = EGL_NO_CONTEXT;
    mEGLConfig = NULL;
}

// 获取EglContext
EGLContext EglCore::getEGLContext() {
    return mEGLContext;
}


// 销毁Surface
void EglCore::releaseSurface(EGLSurface eglSurface) {
    eglDestroySurface(mEGLDisplay, eglSurface);
}

//  创建EGLSurface
EGLSurface EglCore::createWindowSurface(ANativeWindow *surface) {
    assert(surface != NULL);
    if (surface == NULL) {
        ALOGE("ANativeWindow is NULL!");
        return NULL;
    }

    int surfaceAttribs[] = {
            EGL_NONE
    };
    ALOGD("eglCreateWindowSurface start");
    EGLSurface  eglSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, surface, surfaceAttribs);
    checkEglError("eglCreateWindowSurface");
    assert(eglSurface != NULL);
    if (eglSurface == NULL) {
        ALOGE("EGLSurface is NULL!");
        return NULL;
    }

    return eglSurface;
}

// 创建离屏EGLSurface
EGLSurface EglCore::createOffscreenSurface(int width, int height) {
    int surfaceAttribs[] = {
            EGL_WIDTH, width,
            EGL_HEIGHT, height,
            EGL_NONE
    };
    EGLSurface eglSurface = eglCreatePbufferSurface(mEGLDisplay, mEGLConfig, surfaceAttribs);
    assert(eglSurface != NULL);
    if (eglSurface == NULL) {
        ALOGE("Surface was null");
        return NULL;
    }
    return eglSurface;
}

// 切换到当前上下文
void EglCore::makeCurrent(EGLSurface eglSurface){
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        ALOGD("Note: makeCurrent w/o display. \n");
    }

    if (!eglMakeCurrent(mEGLDisplay, eglSurface, eglSurface, mEGLContext)) {

    }
}

// 切换到某个上下文
void EglCore::makeCurrent(EGLSurface drawSurface, EGLSurface readSurface) {
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        ALOGD("Note: makeCurrent w/o display. \n");
    }

    if (!eglMakeCurrent(mEGLDisplay, drawSurface, readSurface, mEGLContext)) {

    }
}

// 没有上下文
void EglCore::makeNothingCurrent() {
    if (!eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT)) {
        // TODO 抛出异常
    }
}
// 交换显示
bool EglCore::swapBuffers(EGLSurface eglSurface) {
    return eglSwapBuffers(mEGLDisplay,eglSurface);
}

// 设置pts
void EglCore::setPresentationTime(EGLSurface eglSurface, long nsecs) {
    eglPresentationTimeANDROID(mEGLDisplay, eglSurface, nsecs);
}
// 判断是否属于当前上下文
bool EglCore::isCurrent(EGLSurface eglSurface) {
    return mEGLContext == eglGetCurrentContext() &&
           eglSurface == eglGetCurrentSurface(EGL_DRAW);
}


// 执行查询
int EglCore::querySurface(EGLSurface eglSurface, int what) {
    int value;
    eglQuerySurface(mEGLContext, eglSurface, what, &value);
    return value;
}

// 查询字符串
const char * EglCore::queryString(int what) {
    return eglQueryString(mEGLDisplay, what);
}
// 获取当前的GLES 版本号
int EglCore::getGlVersion() {
    return mGlVersion;
}

// 检查是否出错
void EglCore::checkEglError(const char *msg) {
    int error;
    if ((error = eglGetError()) != EGL_SUCCESS) {
        // TODO 抛出异常
        ALOGE("%s: EGL error: %x", msg, error);
    }
}