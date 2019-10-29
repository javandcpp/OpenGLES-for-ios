//
//  MediaInit.hpp
//  OpenGLPractice
//
//  Created by developer on 2019/9/20.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef MediaInit_hpp
#define MediaInit_hpp

#ifdef __cplusplus
extern "C"{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
}
#endif


#include <stdio.h>


class MediaInit{
    
public:
    MediaInit();
    virtual ~MediaInit();
};

#endif /* MediaInit_hpp */
