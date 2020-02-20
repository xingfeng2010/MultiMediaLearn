#include "opensl_es_context.h"

#define ALOG_TAG "OpenSLESContext"

OpenSLESContext* OpenSLESContext::instance = new OpenSLESContext();

void OpenSLESContext::init() {
	ALOGI("createEngine");
	SLresult result = createEngine();
	ALOGI("createEngine result is s%", ResultToString(result));
	if (SL_RESULT_SUCCESS == result) {
		ALOGI("Realize the engine object");
		// Realize the engine object
		result = RealizeObject(engineObject);
		if (SL_RESULT_SUCCESS == result) {
			ALOGI("Get the engine interface");
			// Get the engine interface
			result = GetEngineInterface();
		}
	}
}

OpenSLESContext::OpenSLESContext() {
	isInited = false;
}
OpenSLESContext::~OpenSLESContext() {
}

OpenSLESContext* OpenSLESContext::GetInstance() {
	if (!instance->isInited) {
		instance->init();
		instance->isInited = true;
	}
	return instance;
}
