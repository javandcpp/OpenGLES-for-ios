//
//  FFmpegDemux.cpp
//  OpenGLPractice
//
//  Created by developer on 2019/9/20.
//  Copyright © 2019 developer. All rights reserved.
//

#include "FFmpegDemux.hpp"
#include <iostream>
#include <thread>
#include <chrono>

FFmpegDemux::FFmpegDemux(){
    
}

FFmpegDemux::~FFmpegDemux(){
    if(audioCodecContext){
        avcodec_free_context(&audioCodecContext);
        audioCodecContext=nullptr;
    }
    if(videoCodecContext){
        avcodec_free_context(&videoCodecContext);
        videoCodecContext=nullptr;
    }
}

static int callBack(void *p){
    return 0;
}

void ffmpegDemux(const void* obj){

    FFmpegDemux *ffmpegDemux=(FFmpegDemux*)obj;
    
    AVStream *audioStream=ffmpegDemux->audioStream;
    AVStream *videoStream=ffmpegDemux->videoStream;
    
    int ret=0;
    AVFormatContext *avFormatCtx=avformat_alloc_context();
    AVDictionary *opt=NULL;
    
//    av_dict_set(&opt, "probesize", "200", AV_DICT_IGNORE_SUFFIX);
   
    
    avFormatCtx->interrupt_callback.callback=callBack;
    
    
    if((ret=avformat_open_input(&avFormatCtx, ffmpegDemux->url.data(), NULL,NULL)<0)){
    
        av_log(NULL, AV_LOG_WARNING, "avformat_open_input failed!\n");
        return;
    }
    
    av_log(NULL, AV_LOG_WARNING, "avformat_open_input success\n");
    
    if((ret=avformat_find_stream_info(avFormatCtx, NULL)<0)){
        av_log(NULL, AV_LOG_WARNING, "avformat_find_stream_info failed!\n");
        return;
    }
    av_log(NULL,AV_LOG_WARNING, "avformat_find_stream_info success\n");
    
    
    int asIndex=av_find_best_stream(avFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    int vsIndex=av_find_best_stream(avFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    
    ffmpegDemux->audioStreamIdx=asIndex;
    ffmpegDemux->videoStreamIdx=vsIndex;
    
  
    if(asIndex>=0){
        AVCodec* audioCodec=avcodec_find_decoder(avFormatCtx->streams[asIndex]->codecpar->codec_id);
       ffmpegDemux->audioCodecContext=avcodec_alloc_context3(audioCodec);
        int ret=avcodec_parameters_to_context(ffmpegDemux->audioCodecContext,avFormatCtx->streams[asIndex]->codecpar);
        if (ret<0) {
            printf("avcodec_parameters_to_context audio error! \n");
            return;
        }
         ffmpegDemux->ffmpegAudioDecode->setAVCodecContext(ffmpegDemux->audioCodecContext);
         audioStream=avFormatCtx->streams[asIndex];
    }
    
    if(vsIndex>=0){
        AVCodec* videoCodec=avcodec_find_decoder(avFormatCtx->streams[vsIndex]->codecpar->codec_id);
        ffmpegDemux->videoCodecContext=avcodec_alloc_context3(videoCodec);
        int ret=avcodec_parameters_to_context(ffmpegDemux->videoCodecContext,avFormatCtx->streams[vsIndex]->codecpar);
        if (ret<0) {
            printf("avcodec_parameters_to_context audio error! \n");
            return;
        }
        ffmpegDemux->ffmpegVideoDecode->setAVCodecContext(ffmpegDemux->videoCodecContext);
        videoStream=avFormatCtx->streams[vsIndex];
    }
    
  
    
  
    if(!audioStream&&!videoStream){
        av_log(NULL, AV_LOG_WARNING, "audiostream or videostream is NULL");
        return;
    }
    
    AVCodec *audioCodec=nullptr;
    AVCodec *videoCodec=nullptr;
    if (audioStream) {
         audioCodec=avcodec_find_decoder(audioStream->codecpar->codec_id);
        
        if(ffmpegDemux->audioResample){
            ffmpegDemux->audioResample->initAudioResample(audioStream->codecpar);
        }
    }
   
    if (videoStream) {
         videoCodec=avcodec_find_decoder(videoStream->codecpar->codec_id);
    }
   
    
    if(!audioCodec&&!videoCodec){
        
        av_log(NULL, AV_LOG_WARNING, "AudioCodec or VideoCodec is NULL");
        return;
    }

    av_log(NULL, AV_LOG_WARNING, "avcodec_find_decoder success\n");
    
    
   

    AVPacket avPacket;
    av_init_packet(&avPacket);
    
    int frame_count=0;
    struct timeval start;
    for (;;) {
        
        if(frame_count==0){
            gettimeofday(&start, NULL);
        }
        ret=av_read_frame(avFormatCtx, &avPacket);
        if (ret<0||ret==AVERROR(ENOMEM)||ret==AVERROR_EOF) {
            printf("read eof! \n");
            break;
        }else{
            if (avPacket.stream_index==asIndex||avPacket.stream_index==vsIndex) {
                ffmpegDemux->notifyDecode(avPacket);
                if (avPacket.stream_index==vsIndex) {
                    ++frame_count;
                }
                
            }
        }
        
        usleep(10*1000);
        
        if (frame_count>=25) {
            struct timeval end={0};
            gettimeofday(&end, NULL);
            
            int time_interval=((end.tv_sec*1000)-(start.tv_sec*1000))+((end.tv_usec/1000)-(start.tv_usec/1000));
            printf("decode framecount :%d  host_seconds:%d\n",frame_count,time_interval/1000);
            if(time_interval/1000<1){
                int mseconds=1000-time_interval;
                usleep(mseconds*1000);
            }
            
            frame_count=0;
        }
        av_packet_unref(&avPacket);
    }

}

void FFmpegDemux::notifyDecode(AVPacket avPacket){
    if(avPacket.stream_index==audioStreamIdx){
        ffmpegAudioDecode->decode(avPacket);
    }else if (avPacket.stream_index==videoStreamIdx){
        ffmpegVideoDecode->decode(avPacket);
    }
}

void FFmpegDemux::addVideoDecode(FFmpegVideoDecode *decode){
    this->ffmpegVideoDecode =   decode;
}
void FFmpegDemux::addAudioDecode(FFmpegAudioDecode *decode){
    this->ffmpegAudioDecode =   decode;
}


void FFmpegDemux::start(std::string url){
    this->url=url;
    std::thread t1(ffmpegDemux,this);
    t1.detach();
}

AVCodecParameters* FFmpegDemux::getAudioCodecParameters(){
    if(audioStream){
        return audioStream->codecpar;
    }
    
    return NULL;
}

void FFmpegDemux::addAudioResample(AudioResample *audioResample){
    this->audioResample=audioResample;
}
