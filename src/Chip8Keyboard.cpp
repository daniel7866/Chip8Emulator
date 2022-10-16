//
//  Chip8Keyboard.cpp
//  chip8_
//
//  Created by Daniel Fogel on 09/10/2022.
//

#include "Chip8Keyboard.h"

Chip8Keyboard::Chip8Keyboard()
{
    Init();
}
Chip8Keyboard::~Chip8Keyboard(){}

void Chip8Keyboard::Init()
{
    for (int i = 0; i < KEYS_COUNT; i++) {
        keys_[i] = false;
    }
}


/**
 //A way to get key down on raylib:
 
 int keyPressed = GetKeyPressed();
 if(keyPressed)
     key = keyPressed;
 if(key)
 {
     if(IsKeyDown(key))
         std::cout<< ((char)key) << "is down" << std::endl;
     
 }
 */
