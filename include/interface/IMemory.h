//
//  IMemory.h
//  chip8
//
//  Created by Daniel Fogel on 08/10/2022.
//

#ifndef IMemory_h
#define IMemory_h

#include "Config.h"
#include "Type.h"
#include "Iinit.h"

class IMemory : public Iinit {
public:
    virtual byte Read_Memory(const int &address) const = 0;
    virtual void Write_Memory(const byte &val, const int &address) = 0;
    virtual ~IMemory()=0;
};

#endif /* IMemory_h */
