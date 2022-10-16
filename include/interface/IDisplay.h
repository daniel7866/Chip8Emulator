//
//  IDisplay.h
//  chip8
//
//  Created by Daniel Fogel on 14/10/2022.
//

#ifndef IDisplay_h
#define IDisplay_h

#include "Iinit.h"

class IDisplay : public Iinit
{
public:
    virtual void Set_Pixel(const int &x, const int &y, const bool &val) = 0;
    virtual bool Is_Pixel_On(const int &x, const int &y) const = 0;
    virtual ~IDisplay()=0;
};

#endif /* IDisplay_h */
