//
//  Config.h
//  chip8
//
//  Created by Daniel Fogel on 08/10/2022.
//

#ifndef Config_h
#define Config_h

#define MEMORY_SIZE 0xFFF // chip8 has 4kb of memory
#define PROGRAM_ADDRESS 0x200 // programs are loaded at 0x200
#define PROGRAM_BUFFER_SIZE (MEMORY_SIZE - PROGRAM_ADDRESS)

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCREEN_SCALE 20

#define DATA_REGISTERS_COUNT 16 // chip8 has 16 data registers
#define STACK_SIZE 16

#define KEYS_COUNT 16

#define DEFAULT_CHARACTER_SET_COUNT 16 // there are 16 sprites in chip8
#define DEFAULT_CHARACTER_SET_WIDTH 5 // every sprite is 5 bytes long

#endif /* Config_h */
