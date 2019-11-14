//
//  AudioResample.hpp
//  OpenglesForIos
//
//  Created by developer on 2019/10/30.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef AudioResample_hpp
#define AudioResample_hpp

#include <stdio.h>
#ifdef __cplusplus
extern "C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
#include "libswresample/swresample.h"
}
#endif

class AudioResample{
    
public:
    int initAudioResample(AVCodecParameters *in);
    
    AVCodecParameters output;
    
    struct SwrContext *swrCtx=nullptr;
    
    int outChannels=-1;
    int outputFormat=0;
    
    struct SwrContext* getSwrContext();
    
};

#endif /* AudioResample_hpp */
