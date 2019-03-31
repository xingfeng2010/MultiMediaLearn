LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudioencoder
LOCAL_SRC_FILES := ./Mp3Encoder.cpp
LOCAL_LDLIBS += -llog

include $(BUILD_SHARED_LIBRARY)