#include "sound_service.h"
#define ALOG_TAG "SoundService"

SoundService::SoundService() {
	ALOGI("SoundService::SoundService()");
	playingState = PLAYING_STATE_STOPPED;
}

SoundService::~SoundService() {
	ALOGI("SoundService::~SoundService()");
}

SoundService* SoundService::instance = new SoundService();

SoundService* SoundService::GetInstance() {
	return instance;
}

void SoundService::setOnCompletionCallback(JavaVM *g_jvm_param, jobject objParam) {
	g_jvm = g_jvm_param;
	obj = objParam;
}
void SoundService::producePacket() {
	ALOGI("SoundService::producePacket() audio player call back method... ");
	// Read data
	byte* audioBuffer = buffer + (currentFrame % bufferNums) * packetBufferSize;
	int result = -1;
	if (NULL != decoderController) {
		result = decoderController->readSamples(target, packetBufferSize / 2, NULL);
		ALOGI("enter SoundService::producePacket() PLAYING_STATE_PLAYING packetBufferSize=%d, result=%d", packetBufferSize, result);
	}
	// If data is read
	if (0 < result) {
		convertByteArrayFromShortArray(target, result, audioBuffer);
		(*audioPlayerBufferQueue)->Enqueue(audioPlayerBufferQueue, audioBuffer, result * 2);
	} else {
		ALOGI("before DestroyContext");
		//		DestroyContext();
		ALOGI("after DestroyContext");
		JNIEnv *env;
		//Attach主线程
		if (g_jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
			ALOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
		}
		jclass jcls = env->GetObjectClass(obj);
		jmethodID onCompletionCallBack = env->GetMethodID(jcls, "onCompletion", "()V");
		ALOGI("before env->CallVoidMethod");
		env->CallVoidMethod(obj, onCompletionCallBack);
		ALOGI("after env->CallVoidMethod");
		//Detach主线程
		if (g_jvm->DetachCurrentThread() != JNI_OK) {
			ALOGE("%s: DetachCurrentThread() failed", __FUNCTION__);
		}
	}
	currentFrame = (currentFrame + 1) % bufferNums;
}

SLresult SoundService::RegisterPlayerCallback() {
	// Register the player callback
	return (*audioPlayerBufferQueue)->RegisterCallback(audioPlayerBufferQueue, PlayerCallback, this); // player context
}

SLresult SoundService::RegisterSlientPlayerCallback() {
	// Register the player callback
	return (*slientAudioPlayerBufferQueue)->RegisterCallback(slientAudioPlayerBufferQueue, PlayerCallback, this); // player context
}

SLresult SoundService::stop() {
	ALOGI("enter SoundService::stop()");

	playingState = PLAYING_STATE_STOPPED;
	ALOGI("Set the audio player state paused");
	// Set the audio player state playing
	SLresult result = SetAudioPlayerStateStoped();
	if (SL_RESULT_SUCCESS != result) {
		ALOGI("Set the audio player state paused return false");
		return result;
	}
	ALOGI("Set the slient audio player state paused");
	result = SetSlientAudioPlayerStateStoped();
	if (SL_RESULT_SUCCESS != result) {
		ALOGI("Set the slient audio player state paused return false");
		return result;
	}
	DestroyContext();

	ALOGI("out SoundService::stop()");
}

SLresult SoundService::play() {
	ALOGI("enter SoundService::play()...");

	// Set the audio player state playing
	ALOGI("Set the audio player state playing");
	SLresult result = SetAudioPlayerStatePlaying();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	ALOGI("Set the slient audio player state playing");
	result = SetSlientAudioPlayerStatePlaying();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	ALOGI(" Enqueue the first buffer to start");

	playingState = PLAYING_STATE_PLAYING;

	// Enqueue buffer to start
	for (int i = 0; i < bufferNums; i++) {
		int result = -1;
		if (NULL != decoderController) {
			result = decoderController->readSamples(target, packetBufferSize / 2, NULL);
		}
		// If data is read
		if (0 < result) {
			convertByteArrayFromShortArray(target, result, buffer + i * packetBufferSize);
			(*audioPlayerBufferQueue)->Enqueue(audioPlayerBufferQueue, buffer + i * packetBufferSize, result * 2);
		}
	}

	ALOGI("out SoundService::play()...");
}

void SoundService::initSongDecoder(const char* accompanyPath, float percent) {
	ALOGI("enter SoundService::initSongDecoder");
	decoderController = new AccompanyDecoderController();
	int* metaData = new int[2];
	decoderController->getMusicMeta(accompanyPath, metaData);
	accompanySampleRate = metaData[0];
	decoderController->init(accompanyPath, percent);
	/** 预设置buffer的个数是2个,从index为0的位置开始作为第一个 **/
	this->bufferNums = 2;
	this->currentFrame = 0;
	//这个是解码器解码一个packet的buffer的大小
	packetBufferSize = 2 * accompanySampleRate * 2 * percent;
	//我们这里预设置bufferNums个packet的buffer
	bufferSize = packetBufferSize * bufferNums;

	lastCurrentTimeMills = 0;
	seekBaseMillsTime = 0;
	seekStartRecordSeconds = 0;
	seekActualSeconds = 0;

}

SLresult SoundService::initSoundTrack() {
	ALOGI("enter SoundService::initSoundTrack");
//	isRunning = true;
//	pthread_mutex_init(&mLock, NULL);
//	pthread_cond_init(&mCondition, NULL);

	ALOGI("get open sl es Engine");
	SLresult result;
	OpenSLESContext* openSLESContext = OpenSLESContext::GetInstance();
	engineEngine = openSLESContext->getEngine();

	ALOGI("Create output mix object");
	// Create output mix object
	result = CreateOutputMix();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}

	ALOGI("Realize output mix object");
	// Realize output mix object
	result = RealizeObject(outputMixObject);
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}

	ALOGI("Initialize buffer");
	// Initialize buffer
	InitPlayerBuffer();

	ALOGI("Create the buffer queue audio player object");
	// Create the buffer queue audio player object
	result = CreateBufferQueueAudioPlayer();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	result = CreateBufferQueueSlientAudioPlayer();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}

	ALOGI("Realize audio player object");
	// Realize audio player object
	result = RealizeObject(audioPlayerObject);
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	result = RealizeObject(slientAudioPlayerObject);
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}

	ALOGI("Get audio player buffer queue interface");
	// Get audio player buffer queue interface
	result = GetAudioPlayerBufferQueueInterface();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	result = GetSlientAudioPlayerBufferQueueInterface();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}

	ALOGI("Registers the player callback");
	// Registers the player callback
	result = RegisterPlayerCallback();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	result = RegisterSlientPlayerCallback();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}

	ALOGI("Get audio player play interface");
	// Get audio player play interface
	result = GetAudioPlayerPlayInterface();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	result = GetSlientAudioPlayerPlayInterface();
	if (SL_RESULT_SUCCESS != result) {
		return result;
	}
	ALOGI("leave init");
	return SL_RESULT_SUCCESS;
}

int SoundService::getCurrentTimeMills() {
	SLmillisecond position = 0;
//	ALOGI("enter SoundService::getCurrentTimeMills");
	if (playingState == PLAYING_STATE_PLAYING) {
		if (0 != audioPlayerObject && NULL != (*audioPlayerPlay)) {
			SLresult result = (*audioPlayerPlay)->GetPosition(audioPlayerPlay, &position);
		}
		position += seekBaseMillsTime;
		//ALOGI("enter SoundService::getCurrentTimeMills playing position=%d", (int)position);
	} else {
		position = lastCurrentTimeMills;
		//ALOGI("enter SoundService::getCurrentTimeMills stoped position=%d", (int)position);
	}
	lastCurrentTimeMills = position;
	return (int)position;
}

bool SoundService::isPlaying() {
	return playingState != PLAYING_STATE_STOPPED;
}
void SoundService::setVolume(float volume) {
	if (NULL != decoderController) {
		decoderController->setVolume(volume, 1.0f);
	}
}

void SoundService::DestroyContext() {
//	pthread_mutex_lock(&mLock);
	ALOGI("enter SoundService::DestroyContext");
	// Destroy audio player object
	DestroyObject(audioPlayerObject);
	DestroyObject(slientAudioPlayerObject);
	ALOGI("after destroy audioPlayerObject");
	// Free the player buffer
	FreePlayerBuffer();
	ALOGI("after FreePlayerBuffer");
	// Destroy output mix object
	DestroyObject(outputMixObject);
	ALOGI("after destroy outputMixObject");
	//destroy mad decoder
	if (NULL != decoderController) {
		decoderController->destroy();
		delete decoderController;
		decoderController = NULL;
	}
//	isRunning = false;
//	pthread_mutex_unlock(&mLock);
	ALOGI("leave SoundService::DestroyContext");
}
