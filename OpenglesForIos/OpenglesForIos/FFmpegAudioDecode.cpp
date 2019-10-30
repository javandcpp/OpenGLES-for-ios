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
FFmpegAudioDecode::FFmpegAudioDecode(){
    avFrame=av_frame_alloc();
}

FFmpegAudioDecode::~FFmpegAudioDecode(){
    
    
    if (avFrame) {
        av_frame_free(&avFrame);
    }
}


void FFmpegAudioDecode::decode(AVPacket avPacket){
    
    printf("decode audio stream index=%d \n",avPacket.stream_index);
    
     int got_frame=0;
    int ret=avcodec_decode_audio4(avCodecContext, avFrame, &got_frame, &avPacket);
    if (ret<0) {
        printf("avcodec_decode_audio4 error! \n");
    }

    if (got_frame) {
        printf("avcodec_decode_audio4 decode :%d  size:%d\n",got_frame,avFrame->pkt_size);
    }
}


void FFmpegAudioDecode::setAVCodecContext(AVCodecContext *avcodecContext){
    
    this->avCodecContext=avcodecContext;
    int ret=avcodec_open2(avCodecContext, NULL, NULL);
    if (ret<0) {
        printf("FFmpegAudioDecode avcodec_open2 failed! \n");
    }
}


