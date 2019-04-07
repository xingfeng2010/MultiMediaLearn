LOCAL_PATH := $(call my-dir)

# FFmpeg library
include $(CLEAR_VARS)
LOCAL_MODULE := avcodec
LOCAL_SRC_FILES := libavcodec-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avdevice
LOCAL_SRC_FILES := libavdevice-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avfilter
LOCAL_SRC_FILES := libavfilter-6.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avformat
LOCAL_SRC_FILES := libavformat-57.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avutil
LOCAL_SRC_FILES := libavutil-55.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := postproc
LOCAL_SRC_FILES := libpostproc-54.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swresample
LOCAL_SRC_FILES := libswresample-2.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swscale
LOCAL_SRC_FILES := libswscale-4.so
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
                    ./com_player_xingfeng_multimedia_FFmpegNative.cpp

LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/include

LOCAL_LDLIBS += -llog
LOCAL_SHARED_LIBRARIES := avcodec avdevice avfilter avformat avutil postproc swresample swscale

include $(BUILD_SHARED_LIBRARY)