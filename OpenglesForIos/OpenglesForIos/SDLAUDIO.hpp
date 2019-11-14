//
//  SDL_AUDIO.hpp
//  OpenglesForIos
//
//  Created by developer on 2019/10/31.
//  Copyright © 2019 developer. All rights reserved.
//

#ifndef SDL_AUDIO_hpp
#define SDL_AUDIO_hpp

#ifdef __cplusplus
extern "C"{
#include "sdl2/SDL.h"
}
#endif

#include <stdio.h>

class SDLAUDIORender{
public:
    SDLAUDIORender();
    
    int sdlInit(SDL_AudioSpec sdl_AudioSpec);
    
    virtual ~SDLAUDIORender();
};

#endif /* SDL_AUDIO_hpp */
