//
//  ProgramDisplay.h
//  chip8
//
//  Created by Daniel Fogel on 16/10/2022.
//

#ifndef ProgramDisplay_h
#define ProgramDisplay_h

#include "Singleton.h"
//#include "raylib.h"
#include "Config.h"

#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include "../include/Chip8Display.h"

#include "../include/Instance.h"
#include "../include/Chip8.h"
#include <SDL2/SDL.h>

#include <thread>

class ProgramDisplay : Singleton<ProgramDisplay> {
    friend class Singleton<ProgramDisplay>;
public:
    void Game_Loop(int delay);
};

#endif /* ProgramDisplay_h */
