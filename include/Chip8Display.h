//
//  Screen.h
//  chip8
//
//  Created by Daniel Fogel on 10/10/2022.
//

#ifndef Screen_h
#define Screen_h

#include "Config.h"
#include "Iinit.h"
#include "IDisplay.h"
#include <assert.h>

class Chip8Display : public IDisplay {
    bool pixels_[SCREEN_HEIGHT][SCREEN_WIDTH];
    
public:
    Chip8Display();
    ~Chip8Display();
    
    inline virtual void Set_Pixel(const int &x, const int &y, const bool &val) override;
    inline virtual bool Is_Pixel_On(const int &x, const int &y) const override;
    
    virtual void Init() override;
};

inline void Chip8Display::Set_Pixel(const int &x, const int &y, const bool &val)
{
    //assert(((x >= 0) && (x < SCREEN_WIDTH) && (y >= 0) && (y < SCREEN_HEIGHT)) && "Invalid pixel");
    pixels_[y][x] = val;
}

inline bool Chip8Display::Is_Pixel_On(const int &x, const int &y) const
{
    //assert(((x >= 0) && (x < SCREEN_WIDTH) && (y >= 0) && (y < SCREEN_HEIGHT)) && "Invalid pixel");
    return pixels_[y][x];
}

#endif /* Screen_h */
