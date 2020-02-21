LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
./opensl_audio.cpp \
./pcmdata.cpp       \
./SXQueue.cpp

LOCAL_MODULE := libopenslaudio
LOCAL_LDLIBS += -llog -lz -landroid -lEGL -lGLESv2 -lOpenSLES

include $(BUILD_SHARED_LIBRARY)