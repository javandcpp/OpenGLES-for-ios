//
//  H264Frame.h
//  OpenglesForIos
//
//  Created by developer on 2019/10/28.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef H264Frame_h
#define H264Frame_h



typedef struct H264FrameDef
{
    unsigned int    length;
    unsigned char*  dataBuffer;
    
}H264Frame;

typedef struct  H264YUVDef
{
    unsigned int    width;
    unsigned int    height;
    H264Frame       luma;
    H264Frame       chromaB;
    H264Frame       chromaR;
    
}H264YUV_Frame;

#endif /* H264Frame_h */
