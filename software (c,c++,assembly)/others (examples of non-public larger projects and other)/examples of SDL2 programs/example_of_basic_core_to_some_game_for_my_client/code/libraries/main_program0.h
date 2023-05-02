#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>     //IMG_
#include <SDL2/SDL_mixer.h>     //MIX_

#include <stdlib.h>
#include <stdio.h>

struct Global_Variables
{
    const uint16_t width = 800;
    const uint16_t height = 600;

    SDL_UniversalTools0* sdl_universal_tool0;
    UniversalTools0* universal_tool0;
    EnginePhysics2D_0* enginge_physics2D_tool0;
    SDL_Cursor* cursor0;
    SDL_Window* window;
    SDL_Renderer* render;
    uint32_t fps;
};

void init_everything(Global_Variables* global_variables);
void free_everything(Global_Variables* global_variables);



class main_program0
{

//universal_variables:
    Global_Variables* global_variables;             //initialized in constructor;
    bool close_program;

//main_functions_variables:
struct Main_Menu_Variables
{
    //event_variables:
        uint8_t mouse_state = 0;
};

//function_events:
    void event_standard();
    void event_main_menu(Main_Menu_Variables* variables);

public:
    //constructor
    main_program0(Global_Variables* global_variables)
    {
        this->global_variables = global_variables;
    }

//main_functions:
    void main_menu();

    //destructor
    ~main_program0()
    {

    }


};

