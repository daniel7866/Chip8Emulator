//
//  IKeyboard.h
//  chip8
//
//  Created by Daniel Fogel on 09/10/2022.
//

#ifndef IKeyboard_h
#define IKeyboard_h

#include "Iinit.h"

typedef enum Key
{
    Key_0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F
} Key;

class IKeyboard : public Iinit {
public:
    virtual inline int Map(const int &key) = 0;
    //virtual inline int Map_Reverse(const int &key) = 0;
    virtual inline void Key_Up(const int &key) = 0;
    virtual inline void Key_Down(const int &key) = 0;
    
    virtual inline bool Is_Key_Down(const int &key) = 0;
    virtual ~IKeyboard() = 0;
};

#endif /* IKeyboard_h */


/**
 Test the Keyboard:
 
 IKeyboard *keyboard = new Chip8Keyboard();
 
 const int screenWidth = 800;
     const int screenHeight = 450;

     InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

     Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

     SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
     //--------------------------------------------------------------------------------------
 int key = 0;
     // Main game loop
     while (!WindowShouldClose())    // Detect window close button or ESC key
     {
         BeginDrawing();
         
         int keyPressed = GetKeyPressed();
         if(keyPressed)
             key = keyPressed;
         if(key)
         {
             int virtual_key = keyboard->Map(key);
             if(IsKeyDown(key))
             {
                 keyboard->Key_Down(virtual_key);
             }
             else
             {
                 keyboard->Key_Up(virtual_key);
                 key = 0;
             }
             
             if(keyboard->Is_Key_Down(virtual_key))
                 std::cout<< "physical " <<((char)key) << " virtual " << std::hex << virtual_key << " is down " << std::endl;
             else
                 std::cout<< "physical " <<((char)key) << " virtual " << std::hex << virtual_key << " is up " << std::endl;
             
         }

             ClearBackground(RAYWHITE);

             DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

             DrawCircleV(ballPosition, 50, MAROON);

         EndDrawing();
         //----------------------------------------------------------------------------------
     }

     // De-Initialization
     //--------------------------------------------------------------------------------------
     CloseWindow();        // Close window and OpenGL context
     //--------------------------------------------------------------------------------------
 delete keyboard;
 */
