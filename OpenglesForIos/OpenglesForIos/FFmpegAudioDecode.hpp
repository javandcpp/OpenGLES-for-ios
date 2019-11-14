//
//  VideoDecode.hpp
//  OpenGLPractice
//
//  Created by developer on 2019/10/22.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef VideoDecode_hpp
#define VideoDecode_hpp

#include "AudioResample.hpp"

#include <stdio.h>

#ifdef __cplusplus

extern "C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
}

#endif


struct AVPacket;

class FFmpegAudioDecode{
    
public:
    FFmpegAudioDecode();
    
    virtual ~FFmpegAudioDecode();
    
    void decode(AVPacket avpacket);
    
    AVCodecContext *avCodecContext=nullptr;
    
    void setAVCodecContext(AVCodecContext *avcodecContext);
    
    void addAudioResample(AudioResample *audioResample);
    
    AVFrame *avFrame=nullptr;
    
    FILE *file=nullptr;
    
    AudioResample *audioResample=nullptr;
    
};

#endif /* VideoDecode_hpp */
