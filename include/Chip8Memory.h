//
//  Chip8Memory.h
//  chip8
//
//  Created by Daniel Fogel on 08/10/2022.
//

#ifndef Chip8Memory_h
#define Chip8Memory_h

#include "IMemory.h"
#include "Iinit.h"
#include <assert.h>
#include <iostream>

class Chip8Memory : public IMemory {
private:
    byte memory_[MEMORY_SIZE];
    const byte DEFAULT_CHARACTER_SET_[DEFAULT_CHARACTER_SET_COUNT*DEFAULT_CHARACTER_SET_WIDTH] =
    {
        0xF0,   0x90,   0x90,   0x90,   0xF0,   //  0x0
        0x20,   0x60,   0x20,   0x20,   0x70,   //  0x1
        0xF0,   0x10,   0xF0,   0x80,   0xF0,   //  0x2
        0xF0,   0x10,   0xF0,   0x10,   0xF0,   //  0x3
        0x90,   0x90,   0xF0,   0x10,   0x10,   //  0x4
        0xF0,   0x80,   0xF0,   0x10,   0xF0,   //  0x5
        0xF0,   0x80,   0xF0,   0x90,   0xF0,   //  0x6
        0xF0,   0x10,   0x20,   0x40,   0x40,   //  0x7
        0xF0,   0x90,   0xF0,   0x90,   0xF0,   //  0x8
        0xF0,   0x90,   0xF0,   0x10,   0xF0,   //  0x9
        0xF0,   0x90,   0xF0,   0x90,   0x90,   //  0xA
        0xE0,   0x90,   0xE0,   0x90,   0xE0,   //  0xB
        0xF0,   0x80,   0x80,   0x80,   0xF0,   //  0xC
        0xE0,   0x90,   0x90,   0x90,   0xE0,   //  0xD
        0xF0,   0x80,   0xF0,   0x80,   0xF0,   //  0xE
        0xF0,   0x80,   0xF0,   0x80,   0x80   //  0xF
    };
    
    void Load_Sprites_();
public:
    Chip8Memory();
    virtual ~Chip8Memory();
    virtual inline byte Read_Memory(const int &address) const override;
    virtual inline void Write_Memory(const byte &val, const int &address) override;
    virtual void Init() override;
    
    void Load_Game(const char *buffer, const long &size);
};

inline byte Chip8Memory::Read_Memory(const int &address) const
{
    //assert(address >= 0 && address < MEMORY_SIZE);
    return memory_[address];
}

inline void Chip8Memory::Write_Memory(const byte &val, const int &address)
{
    //assert(address >= 0 && address < MEMORY_SIZE);
    memory_[address] = val;
}

#endif /* Chip8Memory_h */
