//
//  Registers.cpp
//  chip8_
//
//  Created by Daniel Fogel on 09/10/2022.
//

#include <stdio.h>
#include <assert.h>
#include "../include/Registers.h"

Registers::Registers()
{
    Init();
}

Registers::~Registers(){}

void Registers::Init()
{
    for (int i = 0; i < DATA_REGISTERS_COUNT; i++) {
        dataRegisters_[i] = 0;
    }
    
    I_ = 0;
    DT_ = 0;
    ST_ = 0;
    SP_ = 0;
    PC_ = 0;
}

void Registers::Write_Register(const RegisterDefines &reg, const word &val)
{
    switch (reg) {
        case RegisterDefines::SP:
            SP_ = val;
            break;
        case RegisterDefines::PC:
            PC_ = val;
            break;
        case RegisterDefines::I:
            I_ = val;
            break;
        case RegisterDefines::DT:
            DT_ = val;
            break;
        case RegisterDefines::ST:
            ST_ = val;
            break;
        default:
            //assert(((reg >= RegisterDefines::V0) && (reg <= RegisterDefines::VF)) && "Attempted to read an invalid register");
            dataRegisters_[reg] = val;
            break;
    }
}

word Registers::Read_Register(const RegisterDefines &reg) const
{
    switch (reg) {
        case RegisterDefines::SP:
            return SP_;
        case RegisterDefines::PC:
            return PC_;
        case RegisterDefines::I:
            return I_;
        case RegisterDefines::DT:
            return DT_;
        case RegisterDefines::ST:
            return ST_;
        default:
            //assert(((reg >= RegisterDefines::V0) && (reg <= RegisterDefines::VF)) && "Attempted to read an invalid register");
            return dataRegisters_[reg];
    }
}
