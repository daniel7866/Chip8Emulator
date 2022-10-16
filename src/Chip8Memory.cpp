//
//  Chip8Memory.cpp
//  chip8_
//
//  Created by Daniel Fogel on 08/10/2022.
//

#include "../include/Chip8Memory.h"

Chip8Memory::Chip8Memory()
{
    Init();
}

Chip8Memory::~Chip8Memory(){}

void Chip8Memory::Init()
{
    for (int i = 0; i < MEMORY_SIZE; i++) // zero out the memory
    {
        memory_[i] = 0;
    }
    
    Load_Sprites_(); // load the sprites to the beginning of the memory
}

void Chip8Memory::Load_Sprites_() { 
    for (int i = 0; i < (DEFAULT_CHARACTER_SET_COUNT * DEFAULT_CHARACTER_SET_WIDTH); i++) {
        memory_[i] = DEFAULT_CHARACTER_SET_[i];
    }
}

void Chip8Memory::Load_Game(const char *buffer, const long &size)
{
    for (int i = 0; i < size; i++) {
        memory_[PROGRAM_ADDRESS + i] = buffer[i];
    }
}

