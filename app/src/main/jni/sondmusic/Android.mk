LOCAL_PATH := $(call my-dir)

# FFmpeg library
include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := libffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudioencoder

LOCAL_SRC_FILES :=  $(LOCAL_PATH)/libmp3lame/bitstream.c \
                    $(LOCAL_PATH)/libmp3lame/encoder.c \
                    $(LOCAL_PATH)/libmp3lame/fft.c \
                    $(LOCAL_PATH)/libmp3lame/gain_analysis.c \
                    $(LOCAL_PATH)/libmp3lame/id3tag.c \
                    $(LOCAL_PATH)/libmp3lame/lame.c \
                    $(LOCAL_PATH)/libmp3lame/mpglib_interface.c \
                    $(LOCAL_PATH)/libmp3lame/newmdct.c \
                    $(LOCAL_PATH)/libmp3lame/presets.c \
                    $(LOCAL_PATH)/libmp3lame/psymodel.c \
                    $(LOCAL_PATH)/libmp3lame/quantize.c \
                    $(LOCAL_PATH)/libmp3lame/quantize_pvt.c \
                    $(LOCAL_PATH)/libmp3lame/reservoir.c \
                    $(LOCAL_PATH)/libmp3lame/set_get.c \
                    $(LOCAL_PATH)/libmp3lame/tables.c \
                    $(LOCAL_PATH)/libmp3lame/takehiro.c \
                    $(LOCAL_PATH)/libmp3lame/util.c \
                    $(LOCAL_PATH)/libmp3lame/vbrquantize.c \
                    $(LOCAL_PATH)/libmp3lame/VbrTag.c \
                    $(LOCAL_PATH)/libmp3lame/version.c \
                    $(LOCAL_PATH)/wrapper.c \
                    $(LOCAL_PATH)/Mp3Encoder.cpp \
                    $(LOCAL_PATH)/mp3_encoder.cpp \
                    $(LOCAL_PATH)/com_player_xingfeng_multimedia_FFmpegNative.cpp \
                    $(LOCAL_PATH)/render/common/Looper.cpp \
                    $(LOCAL_PATH)/render/common/MyLooper.cpp \
                    $(LOCAL_PATH)/render/xinggles/egl_core.cpp \
                    $(LOCAL_PATH)/render/xinggles/EglSurfaceBase.cpp \
                    $(LOCAL_PATH)/render/xinggles/GlShaders.cpp \
                    $(LOCAL_PATH)/render/xinggles/GlUtils.cpp \
                    $(LOCAL_PATH)/render/xinggles/OffscreenSurface.cpp \
                    $(LOCAL_PATH)/render/xinggles/WindowSurface.cpp \
                    $(LOCAL_PATH)/render/xingrender/GLRender.cpp \
                    $(LOCAL_PATH)/render/xingrender/Triangle.cpp \
                    $(LOCAL_PATH)/render/NativeRenderControl.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/include

LOCAL_LDLIBS += -llog -lz -landroid -lEGL -lGLESv2
LOCAL_SHARED_LIBRARIES := ffmpeg

include $(BUILD_SHARED_LIBRARY)
include $(call all-makefiles-under,$(LOCAL_PATH))