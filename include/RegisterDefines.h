//
//  RegisterDefines.h
//  chip8
//
//  Created by Daniel Fogel on 09/10/2022.
//

#ifndef RegisterDefines_h
#define RegisterDefines_h

typedef enum RegisterDefines {
    V0 = 0x0,
    V1 = 0x1,
    V2 = 0x2,
    V3 = 0x3,
    V4 = 0x4,
    V5 = 0x5,
    V6 = 0x6,
    V7 = 0x7,
    V8 = 0x8,
    V9 = 0x9,
    VA = 0xA,
    VB = 0xB,
    VC = 0xC,
    VD = 0xD,
    VE = 0xE,
    VF = 0xF,
    I,
    PC,
    SP,
    DT,
    ST
} RegisterDefines;

#endif /* RegisterDefines_h */
