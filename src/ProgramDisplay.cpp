//
//  ProgramDisplay.cpp
//  chip8_
//
//  Created by Daniel Fogel on 16/10/2022.
//

#include <stdio.h>
#include "../include/ProgramDisplay.h"
/*
void ProgramDisplay::Game_Loop()
{
    const int screenWidth = SCREEN_WIDTH * SCREEN_SCALE;
    const int screenHeight = SCREEN_HEIGHT * SCREEN_SCALE;
    
    InitWindow(screenWidth, screenHeight, "Chip8 Emulator by Daniel Fogel");
    
    SetTargetFPS(50);               // Set our game to run at 60 frames-per-second
    
    Chip8 &chip8 = Instance<Chip8>();
    Chip8Display *display = chip8.Get_Display();
    
    int key = 0;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            for (int j = 0; j < SCREEN_HEIGHT; j++) {
                if(display->Is_Pixel_On(i, j))
                {
                    DrawRectangle(i * SCREEN_SCALE, j * SCREEN_SCALE, SCREEN_SCALE, SCREEN_SCALE, WHITE);
                }
            }
        }
        
        if(chip8.Waiting_For_Key_Press())
        {
            key = GetKeyPressed();
            if(key)
            {
                Instance<Chip8>().Press(key);
                std::cout << Instance<Chip8>().Read_Register(V0);
            }
        }
        
        if(!chip8.Waiting_For_Key_Press())
        {
            int keyPressed = GetKeyPressed();
            if(keyPressed)
            {
                key = keyPressed;
            }
            else
            {
                key = 0;
            }
            if(key)
            {
                if(IsKeyDown(key))
                {
                    chip8.Key_Down(chip8.Map(key));
                    std::cout << "KEY " << chip8.Map(key) << " IS DOWN\n";
                }
                else
                {
                    chip8.Key_Up(chip8.Map(key));
                    std::cout << "KEY " << chip8.Map(key) << " IS DOWN\n";
                }
            }
            chip8.Execute_Instruction();
            
            byte dt = chip8.Read_Register(DT);
            while(dt)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                chip8.Write_Register(DT, dt - 1);
                dt -= 1;
            }
            
            //std::cout << chip8.Read_Register(PC) << std::endl;
        }
        
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}
*/

void ProgramDisplay::Game_Loop(int delay)
{
    Chip8 &chip8 = Instance<Chip8>();
    Chip8Display *display = chip8.Get_Display();
    SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *window = SDL_CreateWindow(
            "Chip8 Emulator by Daniel Fogel",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE, SDL_WINDOW_SHOWN
        );
    SDL_Event event;
    SDL_Rect r;
        SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);
        while(1)
        {
            SDL_Delay(delay);
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {
                    goto out;
                }
                if(event.type == SDL_KEYDOWN)
                {
                    if(event.key.keysym.sym == '=')
                    {
                        delay++;
                        break;
                    }
                    if(event.key.keysym.sym == '-' && delay > 0)
                    {
                        delay--;
                        break;
                    }
                    chip8.Key_Down(chip8.Map((event.key.keysym.sym)));
                    if(chip8.Waiting_For_Key_Press())
                    {
                        chip8.Press(chip8.Map(event.key.keysym.sym));
                    }
                }
                if(event.type == SDL_KEYUP)
                {
                    chip8.Key_Up(chip8.Map(event.key.keysym.sym));
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            
            if(!chip8.Waiting_For_Key_Press())
            {
                chip8.Execute_Instruction();
            }
            
            for (int i = 0; i < SCREEN_WIDTH; i++) {
                for (int j = 0; j < SCREEN_HEIGHT; j++) {
                    if(display->Is_Pixel_On(i, j))
                    {
                        r.x = i * SCREEN_SCALE;
                        r.y = j * SCREEN_SCALE;
                        r.w = SCREEN_SCALE;
                        r.h = SCREEN_SCALE;
                        SDL_RenderFillRect(renderer, &r);
                        //SDL_RenderDrawRect(renderer, &r);
                    }
                }
            }
             
            byte dt = chip8.Read_Register(DT);
            while(dt)
            {
                dt = dt -1;
                chip8.Write_Register(DT, dt);
            }
            
            SDL_RenderPresent(renderer);
        }

    out:
        SDL_DestroyWindow(window);
}
