//
//  MainViewController.m
//  OpenglesForIos
//
//  Created by developer on 2019/10/28.
//  Copyright © 2019 developer. All rights reserved.
//

#import "ViewController.h"





@interface ViewController ()
{
    FFmpegDemux *ffmpegDemux;
    FFmpegVideoDecode *ffmpegVideoDecode;
    FFmpegAudioDecode *ffmpegAudioDecode;
    AudioResample *audioResample;
    OpenglView *openglview;
}
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    MediaInit mediaInit;
    openglview=[[OpenglView alloc] init];
    
//    [openglview setBackgroundColor:[UIColor redColor]];
    [self.view addSubview:openglview];
    
  
    ffmpegDemux=new FFmpegDemux;
    audioResample=new AudioResample;
  
    

    
    ffmpegVideoDecode=new FFmpegVideoDecode;
    ffmpegAudioDecode=new FFmpegAudioDecode;
    
    ffmpegVideoDecode->addOpenglVideoRender(openglview);
    
    ffmpegDemux->addAudioDecode(ffmpegAudioDecode);
    ffmpegDemux->addVideoDecode(ffmpegVideoDecode);
    
    ffmpegDemux->addAudioResample(audioResample);
    ffmpegAudioDecode->addAudioResample(audioResample);
    

    
    
    //    OpenGLRender *openglRender=new OpenGLRender;
    //    openglRender->openglInit();
    //
    //    ffmpegVideoDecode->addOpenglVideoRender(openglRender);
//    https://cdn.kaishuhezi.com/kstory/microcourse/video/c09784ce-b35e-4c1d-a64d-bed13b345673.mp4
    ffmpegDemux->start("https://clips.vorwaerts-gmbh.de/big_buck_bunny.mp4");
  
    //    openglRender->start();
    
    
//    using namespace std;
    
    // Do any additional setup after loading the view.
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
