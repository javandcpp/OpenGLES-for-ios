//
//  VideoDecode.hpp
//  OpenGLPractice
//
//  Created by developer on 2019/10/22.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef VideoDecode_hpp
#define VideoDecode_hpp

#include <stdio.h>

#ifdef __cplusplus

extern "C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
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
    
    AVFrame *avFrame=nullptr;
    
};

#endif /* VideoDecode_hpp */
