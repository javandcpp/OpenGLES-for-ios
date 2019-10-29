//
//  MediaInit.cpp
//  OpenGLPractice
//
//  Created by developer on 2019/9/20.
//  Copyright © 2019 developer. All rights reserved.
//

#include "MediaInit.hpp"

MediaInit::MediaInit(){
    
    av_register_all();
    avformat_network_init();
    printf("ffmpeg configure info:%s \n",avutil_configuration());
    printf("ffmpeg version:%s \n",av_version_info());
}

MediaInit::~MediaInit(){
    
    
    
}
