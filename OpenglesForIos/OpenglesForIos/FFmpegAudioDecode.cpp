//
//  VideoDecode.cpp
//  OpenGLPractice
//
//  Created by developer on 2019/10/22.
//  Copyright © 2019 developer. All rights reserved.
//

#include "FFmpegAudioDecode.hpp"

#ifdef __cplusplus

extern "C"{
#include "libavcodec/avcodec.h"
}

#endif
void FFmpegAudioDecode::decode(AVPacket avPacket){
    
    printf("decode audio stream index=%d \n",avPacket.stream_index);
}


void FFmpegAudioDecode::setAVCodecContext(AVCodecContext *avcodecContext){
    
    this->avCodecContext=avcodecContext;
    int ret=avcodec_open2(avCodecContext, NULL, NULL);
    if (ret<0) {
        printf("FFmpegAudioDecode avcodec_open2 failed! \n");
    }
}


