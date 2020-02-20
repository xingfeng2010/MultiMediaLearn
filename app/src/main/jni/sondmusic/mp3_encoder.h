//
// Created by 李世星 on 2019/4/4.
//

#ifndef MULTIMEDIALEARN_MP3_ENCODER_H
#define MULTIMEDIALEARN_MP3_ENCODER_H


#include <stdio.h>
#include "libmp3lame/lame.h"
#include<malloc.h>

class Mp3Encoder {
    private:
        FILE* pcmFile;
        FILE* mp3File;
        lame_t lameClient;
    public:
        Mp3Encoder() {

        }
        ~Mp3Encoder();
        int Init(const char * pcmFilePath, const char * mp3FilePath, int sampleRate, int channels, int bitRate);
        void Encode();
        void Destroy();
};


#endif //MULTIMEDIALEARN_MP3_ENCODER_H
