#include "packet_queue.h"
#define ALOG_TAG "SongStudioPacketQueue"


PacketQueue::PacketQueue() {
	init();
}

PacketQueue::PacketQueue(const char* queueNameParam) {
	init();
	queueName = queueNameParam;
//	ALOGI("queueName is %s ....", queueName);
}

void PacketQueue::init() {
	int initLockCode = pthread_mutex_init(&mLock, NULL);
//	ALOGI("initLockCode is %d", initLockCode);
	int initConditionCode = pthread_cond_init(&mCondition, NULL);
//	ALOGI("initConditionCode is %d", initConditionCode);
	mNbPackets = 0;
	mFirst = NULL;
	mLast = NULL;
	mAbortRequest = false;
}

PacketQueue::~PacketQueue() {
	//ALOGI("%s ~PacketQueue ....", queueName);
	flush();
	pthread_mutex_destroy(&mLock);
	pthread_cond_destroy(&mCondition);
}

int PacketQueue::size() {
//	ALOGI("%s size ....", queueName);
	pthread_mutex_lock(&mLock);
	int size = mNbPackets;
	pthread_mutex_unlock(&mLock);
	return size;
}

void PacketQueue::flush() {
	//ALOGI("%s flush .... and this time the queue size is %d", queueName, size());
	AudioPacketList *pkt, *pkt1;

	AudioPacket *audioPacket;
	pthread_mutex_lock(&mLock);

	for (pkt = mFirst; pkt != NULL; pkt = pkt1) {
		pkt1 = pkt->next;
		audioPacket = pkt->pkt;
		if(NULL != audioPacket){
//			ALOGI("pkt->pkt is not null will delete....");
			delete audioPacket;
//			ALOGI("delete success....");
		}
//		ALOGI("delete pkt ....");
		delete pkt;
		pkt = NULL;
//		ALOGI("delete success....");
	}
	mLast = NULL;
	mFirst = NULL;
	mNbPackets = 0;

	pthread_mutex_unlock(&mLock);
}

int PacketQueue::put(AudioPacket* pkt) {
	if (mAbortRequest) {
		delete pkt;
		return -1;
	}
//	ALOGI("%s put data ....", queueName);
	AudioPacketList *pkt1 = new AudioPacketList();
	if (!pkt1)
		return -1;
	pkt1->pkt = pkt;
	pkt1->next = NULL;

//	ALOGI("%s get pthread_mutex_lock in put method....", queueName);
	int getLockCode = pthread_mutex_lock(&mLock);
//	ALOGI("%s get pthread_mutex_lock result in put method:  %d", queueName, getLockCode);
	if (mLast == NULL) {
		mFirst = pkt1;
	} else {
		mLast->next = pkt1;
	}

	mLast = pkt1;
	mNbPackets++;
//	ALOGI("%s queue's mNbPackets : %d", queueName, mNbPackets);

	pthread_cond_signal(&mCondition);
//	ALOGI("put realease pthread_mutex_unlock ...");
	pthread_mutex_unlock(&mLock);
//	ALOGI("put realease pthread_mutex_unlock success");

	return 0;

}

/* return < 0 if aborted, 0 if no packet and > 0 if packet.  */
int PacketQueue::get(AudioPacket **pkt, bool block) {
	AudioPacketList *pkt1;
	int ret;

//	ALOGI("%s get pthread_mutex_lock in get method....", queueName);
	int getLockCode = pthread_mutex_lock(&mLock);
//	ALOGI("%s get pthread_mutex_lock result in get method:  %d", queueName, getLockCode);
	for (;;) {
		if (mAbortRequest) {
//			ALOGI("mAbortRequest ....");
			ret = -1;
			break;
		}

		pkt1 = mFirst;
		//		ALOGI("queue's mNbPackets : %d", mNbPackets);
		if (pkt1) {
//			ALOGI("have data ....");
			mFirst = pkt1->next;
			if (!mFirst)
				mLast = NULL;
			mNbPackets--;
//			ALOGI("name is %s queue's mNbPackets : %d", queueName, mNbPackets);
			*pkt = pkt1->pkt;
			delete pkt1;
			pkt1 = NULL;
			ret = 1;
			break;
		} else if (!block) {
//			ALOGI("block ....");
			ret = 0;
			break;
		} else {
//			ALOGI("%s pthread_cond_wait ....", queueName);
			pthread_cond_wait(&mCondition, &mLock);
		}
	}

	//	ALOGI("get realease pthread_mutex_unlock ...");
	pthread_mutex_unlock(&mLock);
	//	ALOGI("get realease pthread_mutex_unlock success");
	return ret;

}

void PacketQueue::abort() {
//	ALOGI("%s abort ....", queueName);
	pthread_mutex_lock(&mLock);
	mAbortRequest = true;
	pthread_cond_signal(&mCondition);
	pthread_mutex_unlock(&mLock);
//	ALOGI("queue abort success");
}
