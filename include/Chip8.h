//
//  Chip8.h
//  chip8
//
//  Created by Daniel Fogel on 14/10/2022.
//

#ifndef Chip8_h
#define Chip8_h

#include <random>
#include "raylib.h"
#include <SDL2/SDL.h>

#include "../include/Singleton.h"

#include "../include/interface/IKeyboard.h"
#include "../include/interface/IMemory.h"

#include "../include/Registers.h"
#include "../include/Chip8Memory.h"
#include "../include/Chip8Display.h"
#include "../include/Chip8Keyboard.h"

class Chip8 : Singleton<Chip8>, public IKeyboard, public IMemory, public IDisplay{
    friend class Singleton<Chip8>;
private:
    IKeyboard *keyboard_;
    IMemory *memory_;
    IDisplay *display_;
    Registers *registers_;
    
    word stack_[STACK_SIZE + 1];
    
    bool waitingForKeyPress_;
    RegisterDefines waitKeyReg_;
        
    Chip8();
    ~Chip8();
    
    bool Draw_Sprite_(const int &x, const int &y, const byte *sprite, const int &length);
    
public:
    // controlling the keyboard
    virtual inline int Map(const int &key) override;
    virtual inline void Key_Up(const int &key) override;
    virtual inline void Key_Down(const int &key) override;
    virtual inline bool Is_Key_Down(const int &key) override;
    
    bool Waiting_For_Key_Press();
    void Press(int key);
    
    // controlling the memory
    virtual byte Read_Memory(const int &address) const override;
    virtual void Write_Memory(const byte &val, const int &address) override;
    
    // controlling the registers
    void Write_Register(const RegisterDefines &reg, const word &val);
    word Read_Register(const RegisterDefines &reg) const;
    
    inline void Push(const word &address);
    inline word Pop();
    
    // controlling the display
    virtual void Set_Pixel(const int &x, const int &y, const bool &val) override;
    virtual bool Is_Pixel_On(const int &x, const int &y) const override;
    
    virtual void Init() override;
    
    void Load_Game(const char *buff, const long &size);
    
    inline word Get_Current_Opcode();
    void Execute_Instruction(const word &opcode);
    inline void Execute_Instruction();
    void Execute_Instruction_Extended(const word &opcode);
    
    void Draw_Sprite(const RegisterDefines &vx, const RegisterDefines &vy, const int &length);
    
    inline Chip8Display * Get_Display();
};

inline int Chip8::Map(const int &key)
{
    return keyboard_->Map(key);
}
inline void Chip8::Key_Up(const int &key)
{
    keyboard_->Key_Up(key);
}
inline void Chip8::Key_Down(const int &key)
{
    keyboard_->Key_Down(key);
}
inline bool Chip8::Is_Key_Down(const int &key)
{
    return keyboard_->Is_Key_Down(key);
}

inline Chip8Display * Chip8::Get_Display()
{
    return (Chip8Display *)this->display_;
}

inline void Chip8::Push(const word &address)
{
    word sp = registers_->Read_Register(SP);
    sp += 1;
    registers_->Write_Register(SP, sp);
    stack_[sp] = address;
}
inline word Chip8::Pop()
{
    word sp = registers_->Read_Register(SP);
    word address = stack_[sp];
    registers_->Write_Register(SP, sp - 1);
    return address;
}

inline word Chip8::Get_Current_Opcode()
{
    word pc = registers_->Read_Register(PC);
    word opcode = ((memory_->Read_Memory(pc) << 8) | (memory_->Read_Memory(pc+1)));
    return opcode;
}

inline void Chip8::Execute_Instruction()
{
    word opcode = Get_Current_Opcode();
    word pc = registers_->Read_Register(PC);
    registers_->Write_Register(PC, pc+0x2);
    Execute_Instruction(opcode);
}

#endif /* Chip8_h */
