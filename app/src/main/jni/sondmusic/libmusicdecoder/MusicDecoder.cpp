#include "com_player_xingfeng_multimedia_audioplay_audiotrack_MusicDecoder.h"
#include "accompany_decoder_controller.h"
#include "../libcommon/native_log.h"

#define ALOG_TAG "MusicDecoder"

AccompanyDecoderController* decoderController = NULL;

JNIEXPORT jint JNICALL Java_com_player_xingfeng_multimedia_audioplay_audiotrack_MusicDecoder_getMusicMeta
  (JNIEnv * env, jobject obj, jstring accompanyFilePathParam, jintArray meta) {
	const char* accompanyFilePath = env->GetStringUTFChars(accompanyFilePathParam, NULL);
	ALOGI("musicPath is %s", accompanyFilePath);
	jint* metaData = env->GetIntArrayElements(meta, 0);
	decoderController = new AccompanyDecoderController();
	decoderController->getMusicMeta(accompanyFilePath, metaData);
	ALOGI("sampleRate is %d", metaData[0]);
	ALOGI("bitrate is %d", metaData[1]);
	env->ReleaseIntArrayElements(meta, metaData, 0);
	env->ReleaseStringUTFChars(accompanyFilePathParam, accompanyFilePath);
	return 0;
}

JNIEXPORT jint JNICALL Java_com_player_xingfeng_multimedia_audioplay_audiotrack_MusicDecoder_openFile
  (JNIEnv * env, jobject obj, jstring accompanyFilePathParam, jfloat packetBufferTimePercent) {
	if(NULL != decoderController) {
		const char* accompanyFilePath = env->GetStringUTFChars(accompanyFilePathParam, NULL);
		decoderController->init(accompanyFilePath, packetBufferTimePercent);
		env->ReleaseStringUTFChars(accompanyFilePathParam, accompanyFilePath);
	}
	return 0;
}

JNIEXPORT jint JNICALL Java_com_player_xingfeng_multimedia_audioplay_audiotrack_MusicDecoder_readSamples
  (JNIEnv * env, jobject obj, jshortArray array, jint size, jintArray extraSlientSampleSize) {
	if(NULL != decoderController) {
		jshort* target = env->GetShortArrayElements(array, 0);
		jint* slientSizeArr = env->GetIntArrayElements(extraSlientSampleSize, 0);
		int result = decoderController->readSamples(target, size, slientSizeArr);
		env->ReleaseIntArrayElements(extraSlientSampleSize, slientSizeArr, 0);
		env->ReleaseShortArrayElements(array, target, 0);
		return result;
	}
	return -1;
}

JNIEXPORT void JNICALL Java_com_player_xingfeng_multimedia_audioplay_audiotrack_MusicDecoder_closeFile
  (JNIEnv * env, jobject obj) {
	if(NULL != decoderController) {
		decoderController->destroy();
		delete decoderController;
		decoderController = NULL;
	}
}
