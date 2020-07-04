//
//  MainViewController.m
//  OpenglesForIos
//
//  Created by developer on 2019/10/28.
//  Copyright © 2019 developer. All rights reserved.
//

#import "ViewController.h"



#define SCREEN_WIDTH ([[UIScreen mainScreen] bounds].size.width)
#define SCREEN_HEIGHT ([[UIScreen mainScreen] bounds].size.height)



@interface ViewController ()
{
    FFmpegDemux *ffmpegDemux;
    FFmpegVideoDecode *ffmpegVideoDecode;
    FFmpegAudioDecode *ffmpegAudioDecode;
    AudioResample *audioResample;
    OpenglView *openglview;
    UIButton *btnPlay;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    MediaInit mediaInit;
    openglview=[[OpenglView alloc] init];
    
//    [openglview setBackgroundColor:[UIColor redColor]];
    [self.view addSubview:openglview];
    
    btnPlay=[[UIButton alloc] initWithFrame:CGRectMake((SCREEN_WIDTH-100)-10, SCREEN_HEIGHT-60, 100, 40)];
    [btnPlay setTitle:@"rotate" forState:UIControlStateNormal];
    [btnPlay setBackgroundColor:[UIColor blackColor]];
    
     [btnPlay addTarget:self action:@selector(rotate) forControlEvents:UIControlEventTouchUpInside];
    
  
    ffmpegDemux=new FFmpegDemux;
    audioResample=new AudioResample;
  
    

    
    ffmpegVideoDecode=new FFmpegVideoDecode;
    ffmpegAudioDecode=new FFmpegAudioDecode;
    
    ffmpegVideoDecode->addOpenglVideoRender(openglview);
    
    ffmpegDemux->addAudioDecode(ffmpegAudioDecode);
    ffmpegDemux->addVideoDecode(ffmpegVideoDecode);
    
    ffmpegDemux->addAudioResample(audioResample);
    ffmpegAudioDecode->addAudioResample(audioResample);
    

    
    
//        OpenGLRender *openglRender=new OpenGLRender;
//        openglRender->openglInit();
    //
//        ffmpegVideoDecode->addOpenglVideoRender(openglRender);
//    https://cdn.kaishuhezi.com/kstory/microcourse/video/c09784ce-b35e-4c1d-a64d-bed13b345673.mp4
    ffmpegDemux->start("https://cdn.kaishuhezi.com/kstory/microcourse/video/c09784ce-b35e-4c1d-a64d-bed13b345673.mp4");
  
//        openglRender->start();
    
    [self.view addSubview:btnPlay];
    
    
//    using namespace std;
    
    // Do any additional setup after loading the view.
}

-(void)rotate{
    
    //    self.player.currentPlaybackTime = self.player.duration * 0.59;
    //    self.view.frame = cgr
    [UIView animateWithDuration:0.3 animations:^{
        openglview.frame = CGRectMake(0, 0, 640, 480);
        [self.view layoutIfNeeded];
        [self _interfaceOrientation:UIInterfaceOrientationLandscapeRight];
    }];
    
    
}

- (void)_interfaceOrientation:(UIInterfaceOrientation)orientation {
    if ([[UIDevice currentDevice] respondsToSelector:@selector(setOrientation:)]) {
        SEL selector = NSSelectorFromString(@"setOrientation:");
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:[UIDevice instanceMethodSignatureForSelector:selector]];
        [invocation setSelector:selector];
        [invocation setTarget:[UIDevice currentDevice]];
        NSInteger val = orientation;
        [invocation setArgument:&val atIndex:2];
        [invocation invoke];
    }
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

-(void)dealloc{
        delete ffmpegDemux;
        delete ffmpegAudioDecode;
        delete ffmpegVideoDecode;
        delete audioResample;
}

@end
