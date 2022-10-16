//
//  main.cpp
//  chip8_
//
//  Created by Daniel Fogel on 08/10/2022.
//

#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include "../include/Chip8Display.h"

#include "../include/Instance.h"
#include "../include/Chip8.h"

#include "../include/ProgramDisplay.h"

#include <SDL2/SDL.h>

void Load_Game_File(int argc, const char * argv[])
{
    std::cout << argv[argc-1] << std::endl;
    std::string path = std::string("/Users/daniel/chip8/chip8/chip8/chip8_/Games/") + argv[1];
    FILE *f = fopen(path.c_str(), "rb");
    if(!f)
    {
        std::cout << "Could not locate the game file\n";
        exit(404);
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::cout << "Size of the program " << size << " bytes\n";
    char buff[size];
    fread(buff, sizeof(byte), size, f);
    Instance<Chip8>().Load_Game(buff,size);
}

int main(int argc, const char * argv[])
{
    std::cout << Instance<Chip8>().Read_Register(V0) << std::endl;
    
    Load_Game_File(argc, argv);
    int delay = 2;//atoi(argv[2]);
    if(argc > 2)
        delay = atoi(argv[2]);
    Instance<ProgramDisplay>().Game_Loop(delay);
    
    return 0;
}
