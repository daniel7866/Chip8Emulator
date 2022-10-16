//
//  Registers.h
//  chip8
//
//  Created by Daniel Fogel on 09/10/2022.
//

#ifndef Registers_h
#define Registers_h

#include "Type.h"
#include "interface/Iinit.h"
#include "Config.h"
#include "RegisterDefines.h"

class Registers : public Iinit {
    byte dataRegisters_[DATA_REGISTERS_COUNT]; // 16 one byte registers (V0 - VF)
    word I_; // The I register is 2 bytes
    
    byte DT_; // Delay Timer register
    byte ST_; // Sound Timer register
    
    word PC_; // Program Counter
    byte SP_; // Stack Pointer
    
public:
    Registers();
    ~Registers();
    void Write_Register(const RegisterDefines &reg, const word &val);
    word Read_Register(const RegisterDefines &reg) const;
    
    virtual void Init() override;
    
};

#endif /* Registers_h */
