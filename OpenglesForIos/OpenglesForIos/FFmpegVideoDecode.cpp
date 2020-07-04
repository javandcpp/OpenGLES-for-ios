//
//  AudioDecode.cpp
//  OpenGLPractice
//
//  Created by developer on 2019/10/22.
//  Copyright © 2019 developer. All rights reserved.
//

#include "FFmpegVideoDecode.hpp"

FFmpegVideoDecode::FFmpegVideoDecode(){
    
    NSString *path=[[[NSBundle mainBundle] bundlePath] stringByAppendingString:@"/file.yuv"];
    file=fopen([path UTF8String], "wb+");
    avFrame=av_frame_alloc();
    
    openglView=[[OpenglView alloc] init];
    
   
}

FFmpegVideoDecode::~FFmpegVideoDecode(){
    if (file) {
        fclose(file);
    }
    
    if(avFrame){
        av_frame_free(&avFrame);
    }
    
    if (dstFrame) {
        av_frame_free(&dstFrame);
    }
}

void FFmpegVideoDecode::decode(AVPacket avPacket){
    printf("decode video stream index=%d \n",avPacket.stream_index);
    int got_picture=0;
   
   
   
    int ret=avcodec_decode_video2(avCodecContext, avFrame, &got_picture, &avPacket);
    if (ret<0) {
        printf("avcodec_decode_video2 error! \n");
    }
    static struct timeval start;
    
    
    if (got_picture) {
        printf("avcodec_decode_video2 decode :%d  width:%d height:%d\n",got_picture,avFrame->width,avFrame->height);
       
    }
    
    
    
   
  
    
   
    H264YUV_Frame *frame=(H264YUV_Frame*)malloc(sizeof(H264YUV_Frame));
    switch (avFrame->format) {
        case AV_PIX_FMT_YUV420P:
            printf("AV_PIX_FMT_YUV420P \n");

//            printf("linesize[0]=%d \n",avFrame->linesize[0]);
//            printf("linesize[1]=%d \n",avFrame->linesize[1]);
//            printf("linesize[2]=%d \n",avFrame->linesize[2]);
//
//            fwrite(avFrame->data[0], avFrame->width*avFrame->height, 1, file);
//            fwrite(avFrame->data[1], avFrame->width*avFrame->height/4, 1, file);
//            fwrite(avFrame->data[2], avFrame->width*avFrame->height/4, 1, file);
//            fflush(file);
//
              dstFrame=av_frame_alloc();
//            av_frame_ref(dstFrame, avFrame);
//
              av_frame_move_ref(dstFrame, avFrame);
           
            memset(frame, 0, sizeof(H264YUV_Frame));
            
            frame->width=dstFrame->width;
            frame->height=dstFrame->height;
            
            frame->luma.length=frame->width*frame->height;
            frame->luma.dataBuffer=(unsigned char*)malloc(frame->luma.length);
            memcpy(frame->luma.dataBuffer, dstFrame->data[0],frame->luma.length);
            
            frame->chromaB.length=frame->width*frame->height/4;
             frame->chromaB.dataBuffer=(unsigned char*)malloc(frame->chromaB.length);
            memcpy(frame->chromaB.dataBuffer, dstFrame->data[1],frame->chromaB.length);
            
            frame->chromaR.length=frame->width*frame->height/4;
            frame->chromaR.dataBuffer=(unsigned char*)malloc(frame->chromaR.length);
            memcpy(frame->chromaR.dataBuffer, dstFrame->data[2],frame->chromaR.length);
            

            
            [this->openGLRender displayYUV420pData:frame];
            
//                [this->openGLRender displayYUV420pData(NULL)];
            
            
//            this->openGLRender->addQueue(dstFrame);
            
//            this->openGLRender->render(dstFrame->data[0], dstFrame->data[1], dstFrame->data[2], dstFrame->width, dstFrame->height, 0);

            break;
            
        case -1:
            printf("unknow format! \n");
            break;
//        default:
//            break;
    }
    
    av_frame_unref(avFrame);
    av_frame_free(&dstFrame);
    if(frame->luma.dataBuffer){
        free(frame->luma.dataBuffer);
        frame->luma.dataBuffer=NULL;
    }
    if(frame->chromaR.dataBuffer){
        free(frame->chromaR.dataBuffer);
        frame->chromaR.dataBuffer=NULL;
    }
    if (frame->chromaB.dataBuffer) {
         free(frame->chromaB.dataBuffer);
        frame->chromaB.dataBuffer=NULL;
    }
    if (frame) {
        free(frame);
        frame=NULL;
    }
  

}


void FFmpegVideoDecode::setAVCodecContext(AVCodecContext *avcodecContext){
      this->avCodecContext=avcodecContext;
    
    int ret=avcodec_open2(avCodecContext, NULL, NULL);
    if (ret<0) {
        printf("FFmpegVideoDecode avcodec_open2 failed! \n");
    }
    
}


void FFmpegVideoDecode::addOpenglVideoRender(OpenglView *openGLRender){
    this->openGLRender=openGLRender;
}
