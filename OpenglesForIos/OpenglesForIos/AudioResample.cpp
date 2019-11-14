//
//  AudioResample.cpp
//  OpenglesForIos
//
//  Created by developer on 2019/10/30.
//  Copyright © 2019 developer. All rights reserved.
//

#include "AudioResample.hpp"

int AudioResample::initAudioResample(AVCodecParameters *in){

    //音频重采样上下文初始化
    swrCtx = swr_alloc();
    swrCtx = swr_alloc_set_opts(swrCtx,
                                av_get_default_channel_layout(in->channels),
                                AV_SAMPLE_FMT_S16,
                                44100,
                                av_get_default_channel_layout(in->channels),
                                (AVSampleFormat) in->format,
                                in->sample_rate,
                                0, 0);
    
    int re = swr_init(swrCtx);
    if (re != 0) {
        printf("swr_init failed!\n");
        return -1;
    } else {
        printf("swr_init success!\n");
    }
    outChannels = in->channels;
    outputFormat = AV_SAMPLE_FMT_S16;
    return 0;
}

struct SwrContext* AudioResample::getSwrContext(){
    return swrCtx;
}
