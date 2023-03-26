#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>     //IMG_
#include <SDL2/SDL_mixer.h>     //MIX_

#include <stdlib.h>
#include <stdio.h>

class main_program0
{

//const variables:
    const uint16_t width = 800;
    const uint16_t height = 600;

//main_variables (u should not changing them):
    SDL_UniversalTools0* sdl_universal_tool0;   //making in "init_everything()";
    UniversalTools0* universal_tool0;            //making in "init_everything()";
    SDL_Window* window;
    SDL_Renderer* render;
    uint32_t fps;

//universal_variables:
    bool close_program;

//event_variables:
    uint32_t mouseX;
    uint32_t mouseY;

//maind_functions_variables:
    struct main_menu_variables
    {
        SDL_Texture* menu_texture;
        SDL_Rect menu_rect;

        uint8_t mouse_state;
        uint8_t key_state;
    }variables;

//other_functions:
    void init_everything();

//function_events:
    void event_standard();
    void event_main_menu();

public:
    main_program0()
    {
        this->fps = 60;

        init_everything();

        this->window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf_error("Creating window failed");
            sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","SDL_CreateWindow failed","ok");
            exit(1);
        }

        this->render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(render==NULL)
        {
            printf_error("Creating render failed");
            sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","SDL_CreateRenderer failed","ok");
            exit(1);
        }

        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
    }

//main_functions:
    void main_menu();

    ~main_program0()
    {
        delete this->sdl_universal_tool0;
        delete this->universal_tool0;
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        IMG_Quit();
        Mix_Quit();
    }


};

