//
//  Chip8.cpp
//  chip8_
//
//  Created by Daniel Fogel on 14/10/2022.
//

#include "../include/Chip8.h"

Chip8::Chip8()
{
    keyboard_ = new Chip8Keyboard();
    memory_ = new Chip8Memory();
    display_ = new Chip8Display();
    registers_ = new Registers();
    waitingForKeyPress_ = false;
}

Chip8::~Chip8()
{
    delete(keyboard_);
    delete(memory_);
    delete(display_);
    delete(registers_);
    
    std::cout << "delete(keyboard_);\n";
    std::cout << "delete(memory_)\n";
    std::cout << "delete(display_)\n";
    std::cout << "delete(registers_)\n";
}

// controlling the memory
byte Chip8::Read_Memory(const int &address) const
{
    return memory_->Read_Memory(address);
}
void Chip8::Write_Memory(const byte &val, const int &address)
{
    memory_->Write_Memory(val, address);
}

// controlling the registers
void Chip8::Write_Register(const RegisterDefines &reg, const word &val)
{
    registers_->Write_Register(reg, val);
}
word Chip8::Read_Register(const RegisterDefines &reg) const
{
    return registers_->Read_Register(reg);
}


// controlling the display
void Chip8::Set_Pixel(const int &x, const int &y, const bool &val)
{
    display_->Set_Pixel(x, y, val);
}
bool Chip8::Is_Pixel_On(const int &x, const int &y) const
{
    return display_->Is_Pixel_On(x, y);
}

bool Chip8::Draw_Sprite_(const int &x, const int &y, const byte *sprite, const int &length)
{
    bool collision = false;
    
    for (int dy = 0; dy < length; dy++)
    {
        byte sprite_row = sprite[dy];
        for (int dx = 0; dx < sizeof(byte)*8; dx++)
        {
            if(sprite_row & (0x80 >> dx)) // check if current pixel in sprite is on - then draw it
            {
                int x_to_draw = (x + dx) % SCREEN_WIDTH;    // wraps around if out of bounds
                int y_to_draw = (y + dy) % SCREEN_HEIGHT;   // wraps around if out of bounds
                
                // sprites are xor'd to the screen and checks for collision
                if(display_->Is_Pixel_On(x_to_draw, y_to_draw))
                {
                    display_->Set_Pixel(x_to_draw, y_to_draw, 0);
                    collision = true;
                }
                else
                {
                    display_->Set_Pixel(x_to_draw, y_to_draw, 1);
                }
                
            }
        }
    }
    return collision;
}

void Chip8::Draw_Sprite(const RegisterDefines &vx, const RegisterDefines &vy, const int &length)
{
    byte sprite[length];
    for (int i = 0; i < length; i++)
    {
        sprite[i] = memory_->Read_Memory(registers_->Read_Register(RegisterDefines::I) + i);
    }
    if(Draw_Sprite_(registers_->Read_Register(vx),
                 registers_->Read_Register(vy),
                 sprite,
                 length))
    {
        registers_->Write_Register(VF, 1); // if there was a collision then VF = 1
    }
    else
    {
        registers_->Write_Register(VF, 0);
    }
}

void Chip8::Load_Game(const char *buff, const long &size)
{
    //assert(PROGRAM_ADDRESS + size < MEMORY_SIZE && "Program is too large to load into memory");
    ((Chip8Memory *)memory_)->Load_Game(buff, size);
    registers_->Write_Register(PC, PROGRAM_ADDRESS); // set the program counter to the beggining of the program
}

void Chip8::Init()
{
    display_->Init();
    memory_->Init();
    keyboard_->Init();
}

void Chip8::Execute_Instruction(const word &opcode)
{
    switch (opcode) {
            // clears the display
        case 0x00E0:
        {
            display_->Init();
            break;
        }
            // ret - set the PC to the address in the top of the stack(SP), then subtract SP by 1
        case 0x00EE:
        {
            registers_->Write_Register(PC, Pop());
            break;
        }
        default:
        {
            Execute_Instruction_Extended(opcode);
            break;
        }
    }
}

void Chip8::Execute_Instruction_Extended(const word &opcode)
{
    word nnn = opcode & 0xFFF;
    switch (opcode ^ nnn) {
            // jump to instruction at 0xnnn
        case 0x1000:
        {
            registers_->Write_Register(PC, nnn);
            break;
        }
            // call to instruction at 0xnnn
        case 0x2000:
        {
            word pc = registers_->Read_Register(PC);
            Push(pc);
            registers_->Write_Register(PC, nnn);
            break;
        }
            // skip next instruction if Vx == kk
        case 0x3000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte kk = opcode & 0x00FF;
            if(registers_->Read_Register(RegisterDefines(x)) == kk)
            {
                word pc = registers_->Read_Register(PC);
                registers_->Write_Register(PC, pc+2);
            }
            break;
        }
            // skip next instruction if Vx != kk
        case 0x4000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte kk = opcode & 0x00FF;
            if(registers_->Read_Register(RegisterDefines(x)) != kk)
            {
                word pc = registers_->Read_Register(PC);
                registers_->Write_Register(PC, pc+2);
            }
            break;
        }
            // skip next instruction if vx = vy
        case 0x5000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte y = (opcode & 0x00F0) >> 4;
            if(registers_->Read_Register(RegisterDefines(x)) == registers_->Read_Register(RegisterDefines(y)))
            {
                word pc = registers_->Read_Register(PC);
                registers_->Write_Register(PC, pc+2);
            }
            break;
        }
            // set Vx = kk
        case 0x6000:
        {
            word x = (opcode & 0x0F00) >> 8;
            byte kk = opcode & 0x00FF;
            registers_->Write_Register(RegisterDefines(x), kk);
            break;
        }
            // sets Vx = Vx + kk
        case 0x7000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte kk = opcode & 0x00FF;
            byte vx = registers_->Read_Register(RegisterDefines(x));
            registers_->Write_Register(RegisterDefines(x), vx + kk);
            break;
        }
            
        case 0x8000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte y = (opcode & 0x00F0) >> 4;
            
            byte suffix = opcode & 0x000F;
            
            switch (suffix) {
                    // sets Vx = Vy
                case 0x0:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    registers_->Write_Register(RegisterDefines(x), vy);
                    break;
                }
                    // sets Vx = Vx | Vy
                case 0x1:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(RegisterDefines(x), vx | vy);
                    break;
                }
                    // sets Vx = Vx & Vy
                case 0x2:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(RegisterDefines(x), vx & vy);
                    break;
                }
                    // sets Vx = Vx ^ Vy
                case 0x3:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(RegisterDefines(x), vx ^ vy);
                    break;
                }
                    // sets Vx = Vx + Vy and if overflow - set VF = 1
                case 0x4:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    
                    if(vx + vy > 0xFF)
                    {
                        registers_->Write_Register(VF, 1);
                    }
                    else
                    {
                        registers_->Write_Register(VF, 0);
                    }
                    
                    registers_->Write_Register(RegisterDefines(x), vx + vy);
                    break;
                }
                    // sets Vx = Vx - Vy and sets VF to NOT borrowed
                case 0x5:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    
                    if(vx > vy){
                        registers_->Write_Register(VF, 1); // not borrowed -> VF = 1
                    }
                    else
                    {
                        registers_->Write_Register(VF, 0);
                    }
                    
                    registers_->Write_Register(RegisterDefines(x), vx - vy);
                    break;
                }
                    // shr vx by 1 - if the LSB is 1 (odd number) then VF = 1 (basically a division by 2 with carry flag)
                case 0x6:
                {
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    if(vx & 0x1)
                    {
                        registers_->Write_Register(VF, 1);
                    }
                    else
                    {
                        registers_->Write_Register(VF, 0);
                    }
                    registers_->Write_Register(RegisterDefines(x), vx >> 1);
                    break;
                }
                    // sets Vx = Vy - Vx and sets VF to NOT borrowed
                case 0x7:
                {
                    byte vy = registers_->Read_Register(RegisterDefines(y));
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    
                    if(vy > vx){
                        registers_->Write_Register(VF, 1); // not borrowed -> VF = 1
                    }
                    else
                    {
                        registers_->Write_Register(VF, 0);
                    }
                    
                    registers_->Write_Register(RegisterDefines(x), vy - vx);
                    break;
                }
                    // shl vx by 1 - if the MSB is 1 then VF = 1 (basically a multiply by 2 with overflow flag)
                case 0xE:
                {
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    if(vx & 0x80)
                    {
                        registers_->Write_Register(VF, 1);
                    }
                    else
                    {
                        registers_->Write_Register(VF, 0);
                    }
                    registers_->Write_Register(RegisterDefines(x), vx << 1);
                    break;
                }
                default:
                    break;
            }
            break;
        } // end of 0x8000
            // skip next instruction if vx != vy
        case 0x9000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte y = (opcode & 0x00F0) >> 4;
            if(registers_->Read_Register(RegisterDefines(x)) != registers_->Read_Register(RegisterDefines(y)))
            {
                word pc = registers_->Read_Register(PC);
                registers_->Write_Register(PC, pc+2);
            }
            break;
        }
            // sets the I register to nnn
        case 0xA000:
        {
            registers_->Write_Register(I, nnn);
            break;
        }
            // jumps to memory location at [v0] + nnn
        case 0xB000:
        {
            registers_->Write_Register(PC, registers_->Read_Register(V0) + nnn);
            break;
        }
            // randomize a bit and AND with the value kk and set it to Vx
        case 0xC000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte kk = opcode & 0x00FF;
            byte random = std::rand() % 0xFF;
            registers_->Write_Register(RegisterDefines(x), kk & random);
            break;
        }
            // draw sprites at (Vx,Vy) from location I in memory, draw n bytes of that sprite ([0,5] bytes)
        case 0xD000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte y = (opcode & 0x00F0) >> 4;
            byte n = (opcode & 0x000F);
            Draw_Sprite(RegisterDefines(x), RegisterDefines(y), n);
            break;
        }
            // keyboard:
        case 0xE000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            byte vx = registers_->Read_Register(RegisterDefines(x));
            bool key_vx = keyboard_->Is_Key_Down(vx);
            
            word pc =registers_->Read_Register(PC);
            
            byte suffix = (opcode & 0x00FF);
            switch (suffix) {
                    // skip next instruction if key with the value of [vx] is pressed
                case 0x9E:
                {
                    if(key_vx){
                        registers_->Write_Register(PC, pc + 0x2);
                    }
                    break;
                }
                    // skip next instruction if key with the value of [vx] is NOT pressed
                case 0xA1:
                {
                    if(!key_vx){
                        registers_->Write_Register(PC, pc + 0x2);
                    }
                    break;
                }
                    
                default:
                    break;
            }
        } // end of 0xE000
            
        case 0xF000:
        {
            byte x = (opcode & 0x0F00) >> 8;
            
            byte suffix = (opcode & 0x00FF);
            switch (suffix) {
                    // store the delay timer value in Vx
                case 0x07:
                {
                    registers_->Write_Register(RegisterDefines(x), registers_->Read_Register(DT));
                    break;
                }
                    // wait for a keypress - then store that key in Vx
                case 0x0A:
                {
                    waitingForKeyPress_ = true;
                    waitKeyReg_ = RegisterDefines(x);
                    
                    // make sure program stops execution while waitingForKeyPress_ == true;
                    break;
                }
                    // set dt=[vx]
                case 0x15:
                {
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(DT, vx);
                    break;
                }
                    // set st=[vx]
                case 0x18:
                {
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(ST, vx);
                    break;
                }
                    // set i = i + [vx]
                case 0x1E:
                {
                    word i = registers_->Read_Register(I);
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(I, i + vx);
                    break;
                }
                    // set I = vx * characted width (5)
                case 0x29:
                {
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    registers_->Write_Register(I, vx*DEFAULT_CHARACTER_SET_WIDTH);
                    break;
                }
                    // represent vx as bcd at memory locations [i], [i+1], [i+2]
                case 0x33:
                {
                    word i = registers_->Read_Register(I);
                    byte vx = registers_->Read_Register(RegisterDefines(x));
                    
                    byte hundreds = vx / 100;
                    byte tens = (vx / 10) % 10;
                    byte ones = vx % 10;
                    
                    memory_->Write_Memory(hundreds, i);
                    memory_->Write_Memory(tens, i+1);
                    memory_->Write_Memory(ones, i+2);
                    break;
                }
                    // store registers V0 through Vx at memory locations i, i+1, ... , i+x
                case 0x55:
                {
                    word i = registers_->Read_Register(I);
                    
                    for (int j = 0; j <= x; j++) {
                        byte vj = registers_->Read_Register(RegisterDefines(j));
                        memory_->Write_Memory(vj, i + j);
                    }
                    
                    break;
                }
                    // load registers V0 through Vx from memory locations i, i+1, ... , i+x
                case 0x65:
                {
                    word i = registers_->Read_Register(I);
                    
                    for (int j = 0; j <= x; j++) {
                        byte vj = memory_->Read_Memory(i + j);
                        registers_->Write_Register(RegisterDefines(j), vj);
                    }
                    
                    break;
                }
                    
                default:
                    break;
            }
        }
        default:
        {
            break;
        }
    }
}

bool Chip8::Waiting_For_Key_Press()
{
    return waitingForKeyPress_;
}

/*
    This is for the 0xFx0A instruction
 */
void Chip8::Press(int key)
{
    waitingForKeyPress_ = false;
    Write_Register(waitKeyReg_, keyboard_->Map(key));
}

