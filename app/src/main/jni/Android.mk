LOCAL_PATH := $(call my-dir)

# FFmpeg library
include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := libffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := libaudioencoder

LOCAL_SRC_FILES :=  ./libmp3lame/bitstream.c \
                    ./libmp3lame/encoder.c \
                    ./libmp3lame/fft.c \
                    ./libmp3lame/gain_analysis.c \
                    ./libmp3lame/id3tag.c \
                    ./libmp3lame/lame.c \
                    ./libmp3lame/mpglib_interface.c \
                    ./libmp3lame/newmdct.c \
                    ./libmp3lame/presets.c \
                    ./libmp3lame/psymodel.c \
                    ./libmp3lame/quantize.c \
                    ./libmp3lame/quantize_pvt.c \
                    ./libmp3lame/reservoir.c \
                    ./libmp3lame/set_get.c \
                    ./libmp3lame/tables.c \
                    ./libmp3lame/takehiro.c \
                    ./libmp3lame/util.c \
                    ./libmp3lame/vbrquantize.c \
                    ./libmp3lame/VbrTag.c \
                    ./libmp3lame/version.c \
                    ./wrapper.c \
                    ./Mp3Encoder.cpp \
                    ./mp3_encoder.cpp \
                    ./com_player_xingfeng_multimedia_FFmpegNative.cpp \
                    ./render/common/Looper.cpp \
                    ./render/common/MyLooper.cpp \
                    ./render/xinggles/egl_core.cpp \
                    ./render/xinggles/EglSurfaceBase.cpp \
                    ./render/xinggles/GlShaders.cpp \
                    ./render/xinggles/GlUtils.cpp \
                    ./render/xinggles/OffscreenSurface.cpp \
                    ./render/xinggles/WindowSurface.cpp \
                    ./render/xingrender/GLRender.cpp \
                    ./render/xingrender/Triangle.cpp \
                    ./render/NativeRenderControl.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/include

LOCAL_LDLIBS += -llog -lz -landroid -lEGL -lGLESv2
LOCAL_SHARED_LIBRARIES := ffmpeg

include $(BUILD_SHARED_LIBRARY)