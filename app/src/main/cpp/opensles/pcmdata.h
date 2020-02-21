//
// Created by 李世星 on 2020/2/21.
//

#ifndef MULTIMEDIALEARN_PCMDATA_H
#define MULTIMEDIALEARN_PCMDATA_H

class pcmdata {

public:
    char *data;
    int size;

public:
    pcmdata(char* data, int size);
    ~pcmdata();

    int getSize();

    char* getData();


};

#endif //MULTIMEDIALEARN_PCMDATA_H
