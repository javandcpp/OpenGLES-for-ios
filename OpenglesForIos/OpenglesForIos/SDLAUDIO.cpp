////
////  SDL_AUDIO.cpp
////  OpenglesForIos
////
////  Created by developer on 2019/10/31.
////  Copyright © 2019 developer. All rights reserved.
////
//
//#include "SDLAUDIO.hpp"
//SDLAUDIORender::SDLAUDIORender(){
//    
//}
//
//SDLAUDIORender::~SDLAUDIORender(){
//    
//    
//    
//}
//
//int SDLAUDIORender::sdlInit(SDL_AudioSpec sdl_AudioSpec){
//    
//    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
//        printf( "Could not initialize SDL - %s\n", SDL_GetError());
//        return -1;
//    }
//    //SDL_AudioSpec
////    SDL_AudioSpec wanted_spec;
////    wanted_spec.freq = 44100;
////    wanted_spec.format = AUDIO_S16SYS;
////    wanted_spec.channels = 2;
////    wanted_spec.silence = 0;
////    wanted_spec.samples = 1024;
////    wanted_spec.callback = fill_audio;
//    
//    if (SDL_OpenAudio(&sdl_AudioSpec, NULL)<0){
//        printf("can't open audio.\n");
//        return -1;
//    }
//   
//    return 0;
//}
