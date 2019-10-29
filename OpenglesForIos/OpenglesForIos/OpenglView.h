//
//  OpenglView.h
//  OpenglesForIos
//
//  Created by developer on 2019/10/28.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef OPENG_VIEW_H
#define OPENG_VIEW_H

#import <UIKit/UIKit.h>

#include "H264Frame.h"
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGL.h>
#include <sys/time.h>






@interface OpenglView : UIView
{

/**
 OpenGL绘图上下文
 */
EAGLContext             *_glContext;

/**
 帧缓冲区
 */
GLuint                  _framebuffer;

/**
 渲染缓冲区
 */
GLuint                  _renderBuffer;

/**
 着色器句柄
 */
GLuint                  _program;

/**
 YUV纹理数组
 */
GLuint                  _textureYUV[3];

/**
 视频宽度
 */
GLuint                  _videoW;

/**
 视频高度
 */
GLuint                  _videoH;

GLsizei                 _viewScale;

//void                    *_pYuvData;

#ifdef DEBUG
struct timeval      _time;
NSInteger           _frameRate;
#endif
}

#pragma mark - 接口
- (void)displayYUV420pData:(H264YUV_Frame *) frame;
- (void)setVideoSize:(GLuint)width height:(GLuint)height;
/**
 清除画面
 */
- (void)clearFrame;


@end



#endif
