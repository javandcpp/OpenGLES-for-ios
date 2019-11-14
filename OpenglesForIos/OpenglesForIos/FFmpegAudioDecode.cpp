//
//  VideoDecode.cpp
//  OpenGLPractice
//
//  Created by developer on 2019/10/22.
//  Copyright © 2019 developer. All rights reserved.
//

#include "FFmpegAudioDecode.hpp"
#import <UIKit/UIKit.h>
#ifdef __cplusplus

extern "C"{
#include "libavcodec/avcodec.h"
}

#endif
FFmpegAudioDecode::FFmpegAudioDecode(){
    avFrame=av_frame_alloc();
    NSString *path=[[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/file.pcm"];
    file=fopen([path UTF8String], "wb+");
    
    NSLog(@"path:%@",path);

}

FFmpegAudioDecode::~FFmpegAudioDecode(){
    
    
    if (avFrame) {
        av_frame_free(&avFrame);
    }
    
    if (file) {
        fclose(file);
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
    
    if(NULL == avFrame)
    {
      
        printf("avFrame is null \n");
        return;
    }
    int  t_data_size = av_samples_get_buffer_size(
                                                  NULL, avFrame->channels,
                                                  avFrame->nb_samples,
                                                  (AVSampleFormat)avFrame->format,
                                                  0);
    if(t_data_size < 0)
    {
        printf("av_samples_get_buffer_size: %d \n",t_data_size);
        return;
    }
    if(av_sample_fmt_is_planar((AVSampleFormat)avFrame->format))
    {//如果是平面的
    
        
        int outsize =avFrame->nb_samples * av_get_bytes_per_sample((AVSampleFormat) audioResample->outputFormat)*audioResample->outChannels;
        uint8_t *outArr[2] = {0};
        int linesize=0;
        av_samples_alloc(outArr, &linesize, audioResample->outChannels,avFrame->nb_samples, (enum AVSampleFormat)audioResample->outputFormat, 1);
        
        struct SwrContext * swrCtx=audioResample->getSwrContext();
       
        int len=swr_convert(swrCtx,(uint8_t **)outArr, avFrame->nb_samples, (const uint8_t **)avFrame->data, avFrame->nb_samples);
        
        printf("%d \n",len);
        if (len<=0) {
            return;
        }
//
//        fwrite(outArr[0], outsize, 1,file);
//        fflush(file);
        
        
//        memset(outArr[0], 0, outsize);
//        free(outArr[0]);
    }
    else
    {
        printf("not planar data\n");
//        outPcmFilePtr->write((const char *)inFrame->data[0],t_data_size);
//        outPcmFilePtr->flush();
    }
  
}


void FFmpegAudioDecode::setAVCodecContext(AVCodecContext *avcodecContext){
    
    this->avCodecContext=avcodecContext;
    int ret=avcodec_open2(avCodecContext, NULL, NULL);
    if (ret<0) {
        printf("FFmpegAudioDecode avcodec_open2 failed! \n");
    }
}


void FFmpegAudioDecode::addAudioResample(AudioResample *audioResample){
    this->audioResample=audioResample;
}

