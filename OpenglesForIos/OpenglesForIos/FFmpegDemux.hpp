//
//  FFmpegDemux.hpp
//  OpenGLPractice
//
//  Created by developer on 2019/9/20.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef FFmpegDemux_hpp
#define FFmpegDemux_hpp
#ifdef __cplusplus
extern "C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/avutil.h"
}
#endif
#include <stdio.h>
#include <iostream>
#include "FFmpegAudioDecode.hpp"
#include "FFmpegVideoDecode.hpp"
#include "AudioResample.hpp"

class FFmpegDemux{
    
public:
    
    FFmpegDemux();
    ~FFmpegDemux();
    
   // virtual void demux(std::string url) override;
    
    std::string url;
    
    void start(std::string url);
    
    void notifyDecode(AVPacket avPacket);
    
    void addVideoDecode(FFmpegVideoDecode *decode);
    void addAudioDecode(FFmpegAudioDecode *decode);
    
    AVCodecParameters* getAudioCodecParameters();
    
    void addAudioResample(AudioResample *audioResample);
    
    int audioStreamIdx=-1;
    
    int videoStreamIdx=-1;
    
    AudioResample *audioResample=nullptr;
    

  
//
    FFmpegAudioDecode *ffmpegAudioDecode=nullptr;

    FFmpegVideoDecode *ffmpegVideoDecode=nullptr;
    
    AVStream *videoStream=nullptr;
    
    AVStream *audioStream=nullptr;
    
    AVCodecContext *audioCodecContext=nullptr;

    AVCodecContext *videoCodecContext=nullptr;

  
};

#endif /* FFmpegDemux_hpp */
