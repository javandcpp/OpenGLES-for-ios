//
//  AudioDecode.hpp
//  OpenGLPractice
//
//  Created by developer on 2019/10/22.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef AudioDecode_hpp
#define AudioDecode_hpp
#include <stdio.h>
#include "OpenglView.h"
//#include "OpenGLRender.hpp"
#ifdef __cplusplus

extern "C"{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "sdl2/SDL_log.h"

}

#endif


class FFmpegVideoDecode{
    
public:
    
    FFmpegVideoDecode();
  
    virtual ~FFmpegVideoDecode();
    
    void decode(AVPacket avPacket);
    
     AVCodecContext *avCodecContext=nullptr;
    
    void setAVCodecContext(AVCodecContext *avcodecContext);
    
    FILE *file=nullptr;
    
    AVFrame *avFrame=nullptr;
    
    AVFrame *dstFrame=nullptr;
    
    OpenglView *openglView=nullptr;
    
    OpenglView *openGLRender=nullptr;
    
    void addOpenglVideoRender(OpenglView *openglRender);
    
private:
    AVCodecContext *audioCodecContex=nullptr;
};
#endif /* AudioDecode_hpp */
