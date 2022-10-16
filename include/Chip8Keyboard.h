//
//  Chip8Keyboard.h
//  chip8
//
//  Created by Daniel Fogel on 09/10/2022.
//

#ifndef Chip8Keyboard_h
#define Chip8Keyboard_h

#include "IKeyboard.h"
#include "Iinit.h"
#include "Config.h"
#include "raylib.h"
#include <assert.h>

class Chip8Keyboard : public IKeyboard {
    bool keys_[KEYS_COUNT];
    
public:
    Chip8Keyboard();
    virtual ~Chip8Keyboard();
    
    virtual void Init() override;
    
    virtual inline int Map(const int &key) override;
    //virtual inline int Map_Reverse(const int &key) override;
    virtual inline void Key_Up(const int &key) override; // make all inline
    virtual inline void Key_Down(const int &key) override;
    
    virtual inline bool Is_Key_Down(const int &key) override;
};


inline void Chip8Keyboard::Key_Up(const int &key)
{
    //assert(((key >= Key::Key_0) && (key <= Key::Key_F)) && "Invalid Key");
    keys_[key] = false;
}

inline void Chip8Keyboard::Key_Down(const int &key)
{
    //assert(((key >= Key::Key_0) && (key <= Key::Key_F)) && "Invalid Key");
    keys_[key] = true;
}

inline bool Chip8Keyboard::Is_Key_Down(const int &key)
{
    //assert(((key >= Key::Key_0) && (key <= Key::Key_F)) && "Invalid Key");
    return keys_[key];
}

/**
 The map function will map a pressed key from the raylib library ( actual key on the physical keyboard ) to the virtual key on the emulator:
    The virtual keyboard on the emulator:
            1   2   3   C
            4   5   6   D
            7   8   9   E
            A   0   B   F
    The physical keyboard:
            1   2   3   4
            Q   W   E   R
            A   S   D   F
            Z   X   C   V
 */

inline int Chip8Keyboard::Map(const int &key)
{
    switch ((char )key) {
        case '1':
            return Key::Key_1;
        case '2':
            return Key::Key_2;
        case '3':
            return Key::Key_3;
        case '4':
            return Key::Key_C;
        case 'q':
            return Key::Key_4;
        case 'w':
            return Key::Key_5;
        case 'e':
            return Key::Key_6;
        case 'r':
            return Key::Key_D;
        case 'a':
            return Key::Key_7;
        case 's':
            return Key::Key_8;
        case 'd':
            return Key::Key_9;
        case 'f':
            return Key::Key_E;
        case 'z':
            return Key::Key_A;
        case 'x':
            return Key::Key_0;
        case 'c':
            return Key::Key_B;
        case 'v':
            return Key::Key_F;
        default:
            //assert(false && "Invalid key!");
            return Key::Key_F;
    }
}

/*
// get a virtual key and return a raylib physical key
inline int Chip8Keyboard::Map_Reverse(const int &key)
{
    switch ((Key)key) {
        case Key::Key_1:
            return KeyboardKey::KEY_ONE;
        case Key::Key_2:
            return KeyboardKey::KEY_TWO;
        case Key::Key_3:
            return KeyboardKey::KEY_THREE;
        case Key::Key_C:
            return KeyboardKey::KEY_FOUR;
        case Key::Key_4:
            return KeyboardKey::KEY_Q;
        case Key::Key_5:
            return KeyboardKey::KEY_W;
        case Key::Key_6:
            return KeyboardKey::KEY_E;
        case Key::Key_D:
            return KeyboardKey::KEY_R;
        case Key::Key_7:
            return KeyboardKey::KEY_A;
        case Key::Key_8:
            return KeyboardKey::KEY_S;
        case Key::Key_9:
            return KeyboardKey::KEY_D;
        case Key::Key_E:
            return KeyboardKey::KEY_F;
        case Key::Key_A:
            return KeyboardKey::KEY_Z;
        case Key::Key_0:
            return KeyboardKey::KEY_X;
        case Key::Key_B:
            return KeyboardKey::KEY_C;
        case Key::Key_F:
            return KeyboardKey::KEY_V;
        default:
            assert(false && "Invalid key!");
            return Key::Key_F;
    }
}
*/
#endif /* Chip8Keyboard_h */
