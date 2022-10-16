//
//  Screen.cpp
//  chip8_
//
//  Created by Daniel Fogel on 10/10/2022.
//

#include <stdio.h>
#include "../include/Chip8Display.h"

Chip8Display::Chip8Display()
{
    Init();
}

Chip8Display::~Chip8Display(){}

void Chip8Display::Init()
{
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            pixels_[y][x] = 0;
        }
    }
}
