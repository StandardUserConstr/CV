#include "../libraries/tools0.h"
#include "../libraries/main_program0.h"

void main_program0::init_everything()
{
        if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
        {
            printf_error("Initialization SDL2 failed");
            exit(1);
        }

        this->sdl_universal_tool0 = new SDL_UniversalTools0(this->fps);
        this->universal_tool0 = new UniversalTools0();

        if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)!=(IMG_INIT_JPG|IMG_INIT_PNG))
        {
            printf_error("Initialization SDL2_image failed");
            sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Initialization SDL2_image failed","ok");
            exit(1);

        }
        if(Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC)!=(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC))
        {
            printf_error("Initialization SDL2_mix failed");
            sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Initialization SDL2_mix failed","ok");
            exit(1);
        }
        return;
}

void main_program0::event_standard()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                this->close_program = 1;
            break;

            default:
                break;
        }
    }
    return;
}

void main_program0::event_main_menu()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                this->close_program = 1;
            break;

            case SDL_MOUSEMOTION:
                {
                    this->mouseX = event.motion.x;
                    this->mouseY = event.motion.y;
                    if((this->mouseX>=24 && this->mouseX<=380) && (this->mouseY>=236 && this->mouseY<=396))
                    {
                        this->variables.mouse_state = 1;
                    }
                    else this->variables.mouse_state = 0;

                }
            break;

            default:
                break;
        }
    }
    return;

}

void main_program0::main_menu()
{
    SDL_TextureRectOperations obiekt0;
    obiekt0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"files/images/001.png"));
    obiekt0.texture_rect_vector.rect.push_back({24,236,356,160});

//main_menu_variables
//=========================================
    this->variables.menu_texture = IMG_LoadTexture(this->render,"files/images/000.png");
    this->variables.menu_rect = {0,0,800,600};
    this->variables.mouse_state = 0;
    this->variables.key_state = 0;
//=========================================

//global variables from class main_program0
//=========================================
    this->close_program = 0;
//=========================================

    //SDL_SetWindowFullscreen(this->window,SDL_WINDOW_FULLSCREEN);
    while(this->close_program==0)
    {
            this->sdl_universal_tool0->FpsControl_StartFrame();

            SDL_RenderClear(this->render);
            SDL_RenderCopy(this->render,variables.menu_texture,NULL,&variables.menu_rect);
            this->event_main_menu();
            switch(this->variables.mouse_state)
            {
                case 0:
                    break;
                case 1:
                    SDL_RenderCopy(this->render,obiekt0.texture_rect_vector.texture[0],0,&obiekt0.texture_rect_vector.rect[0]);
                    break;
                default:
                    break;
            }
            switch(this->variables.key_state)
            {
                case 0:
                    break;
                default:
                    break;
            }
            SDL_RenderPresent(this->render);

            this->sdl_universal_tool0->FpsControl_EndFrame();
    }
    obiekt0.Free_Textures_Clear_Rects_Reset_Object_Settings();
    SDL_DestroyTexture(this->variables.menu_texture);

    return;
}
