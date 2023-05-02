#include "../libraries/tools0.h"
#include "../libraries/main_program0.h"

void init_everything(Global_Variables* global_variables)
{
        if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
        {
            printf_error("Initialization SDL2 failed");
            exit(1);
        }

        global_variables->sdl_universal_tool0 = new SDL_UniversalTools0(global_variables->fps);
        global_variables->universal_tool0 = new UniversalTools0();
        global_variables->enginge_physics2D_tool0 = new EnginePhysics2D_0();

        SDL_Surface* cursor_surface = IMG_Load("files/images/009.png");
        global_variables->cursor0 = SDL_CreateColorCursor(cursor_surface, 0, 0);
        SDL_SetCursor(global_variables->cursor0);
        SDL_FreeSurface(cursor_surface);

        if(IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)!=(IMG_INIT_JPG|IMG_INIT_PNG))
        {
            printf_error("Initialization SDL2_image failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Initialization SDL2_image failed","ok");
            exit(1);

        }
        if(Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC)!=(MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_FLAC))
        {
            printf_error("Initialization SDL2_mix failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Initialization SDL2_mix failed","ok");
            exit(1);
        }

        global_variables->fps = 60;

        global_variables->window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,global_variables->width,global_variables->height,SDL_WINDOW_SHOWN);
        if(global_variables->window==NULL)
        {
            printf_error("Creating window failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","SDL_CreateWindow failed","ok");
            exit(1);
        }

        global_variables->render = SDL_CreateRenderer(global_variables->window, -1, SDL_RENDERER_ACCELERATED);
        if(global_variables->render==NULL)
        {
            printf_error("Creating render failed");
            global_variables->sdl_universal_tool0->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","SDL_CreateRenderer failed","ok");
            exit(1);
        }

        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);
        SDL_SetRenderDrawColor(global_variables->render,255,255,255,255);
        return;
}

void free_everything(Global_Variables* global_variables)
{
    delete global_variables->sdl_universal_tool0;
    delete global_variables->universal_tool0;
    delete global_variables->enginge_physics2D_tool0;
    SDL_FreeCursor(global_variables->cursor0);
    SDL_DestroyRenderer(global_variables->render);
    SDL_DestroyWindow(global_variables->window);
    Mix_CloseAudio();
    IMG_Quit();
    Mix_Quit();
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

void main_program0::event_main_menu(main_program0::Main_Menu_Variables* variables)
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
                    if((event.motion.x>=24 && event.motion.x<=380) && (event.motion.y>=236 && event.motion.y<=396))
                    {
                        if(variables->mouse_state != 2) variables->mouse_state = 1;
                    }
                    else variables->mouse_state = 0;

                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                {
                    switch(variables->mouse_state)
                    {
                        case 1:
                            {
                                if(event.button.button == SDL_BUTTON_LEFT) variables->mouse_state = 2;
                            }
                            break;

                        default:
                            break;
                    }
                }
            break;


            case SDL_MOUSEBUTTONUP:
                {
                    switch(variables->mouse_state)
                    {
                        case 2:
                            {
                                if(event.button.button == SDL_BUTTON_LEFT) variables->mouse_state = 3;
                            }
                            break;

                        default:
                            break;
                    }
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
    obiekt0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->global_variables->render,"files/images/001.png"));
    obiekt0.texture_rect_vector.rect.push_back({24,236,356,160});

    Main_Menu_Variables variables;
    SDL_Texture* background_texture = IMG_LoadTexture(this->global_variables->render,"files/images/000.png");
    SDL_Rect background_rect = {0,0,800,600};
    this->close_program = 0;

    //SDL_SetWindowFullscreen(this->window,SDL_WINDOW_FULLSCREEN);
    this->global_variables->sdl_universal_tool0->Set_Texture_Opacity_To_Zero_In_Instant(background_texture);
    this->global_variables->sdl_universal_tool0->Set_Texture_Opacity_To_Zero_In_Instant(obiekt0.texture_rect_vector.texture[0]);
    while(this->close_program==0)
    {
            this->global_variables->sdl_universal_tool0->FpsControl_StartFrame();

            SDL_RenderClear(this->global_variables->render);
            SDL_RenderCopy(this->global_variables->render,background_texture,NULL,&background_rect);

            this->event_main_menu(&variables);
            switch(variables.mouse_state)
            {
                case 0:
                    //obiekt0.Reset_Object_Settings();
                    break;
                case 1:
                    /*if(obiekt0.Paste_Specified_texture_To_Renderer_In_Opacity_Wave_One_Loop(this->global_variables->render,0,0.034,5)==SDL_TextureRectOperations::OPERATION_DONE)
                    {
                        obiekt0.Reset_Paste_Specified_texture_To_Renderer_In_Opacity_Wave_One_Loop();
                    }
                    SDL_RenderCopy(this->global_variables->render,obiekt0.texture_rect_vector.texture[0],0,&obiekt0.texture_rect_vector.rect[0]);*/
                    /*if(obiekt0.Paste_Specified_texture_To_Renderer_Down_Up_Physics_One_Loop(this->global_variables->render,0,9.0,0.04,-80)==10)
                    {
                        //obiekt0.Reset_Paste_Specified_texture_To_Renderer_Down_Up_Physics_One_Loop();
                    }*/
                    //obiekt0.Paste_Specified_texture_To_Renderer_Up_Down_Physics(this->global_variables->render,0,8.0,0.045,0.67,440);
                    //obiekt0.Paste_Specified_texture_To_Renderer_Down_Up_Physics(this->global_variables->render,0,8.0,0.045,0.90,0);
                    //obiekt0.Paste_Specified_texture_To_Renderer_Up_Down_Physics_One_Loop(this->global_variables->render,0,8.0,0.035,440);
                    //obiekt0.texture_rect_vector.rect[0].x++;
                    //obiekt0.Paste_Specified_texture_To_Renderer_Down_Physics_One_Loop(this->global_variables->render,0,0.6500,9.80,400,60);
                    //obiekt0.texture_rect_vector.rect[0].x++;
                    global_variables->enginge_physics2D_tool0->Change_Specified_rect_Down_Physics(&obiekt0.texture_rect_vector.rect[0].y,1.00,9.80,400,0.854,60);
                    global_variables->enginge_physics2D_tool0->Change_Specified_rect_Left_Right_Physics(&obiekt0.texture_rect_vector.rect[0].x,0.995,10.0,0.85,500,-10,0,0.05);
                    /*obiekt0.Change_Specified_texture_In_Opacity_Wave_One_Loop(0,0.061,0.4,0.01,0.071);
                    if(obiekt0.Is_Change_Specified_texture_In_Opacity_Wave_One_Loop_DONE()==1)
                    {
                        obiekt0.Reset_Change_Specified_texture_In_Opacity_Wave_One_Loop();
                    }*/
                    SDL_RenderCopy(this->global_variables->render,obiekt0.texture_rect_vector.texture[0],0,&obiekt0.texture_rect_vector.rect[0]);
                    break;
                case 2:
                    printf("wcisnieto lewy przycisk myszy\n");
                    //obiekt0.Reset_Object_Settings();
                    break;
                case 3:
                    printf("puszczono lewy przycisk myszy\n");
                    variables.mouse_state = 1;
                    //obiekt0.Reset_Object_Settings();
                    break;
                default:
                    break;
            }

            SDL_RenderPresent(this->global_variables->render);

            this->global_variables->sdl_universal_tool0->Change_Texture_Opacity_To_Max(background_texture,2);
            this->global_variables->sdl_universal_tool0->Change_Texture_Opacity_To_Max(obiekt0.texture_rect_vector.texture[0],2);

            this->global_variables->sdl_universal_tool0->FpsControl_EndFrame();
    }
    obiekt0.Free_Textures_Clear_Rects_Reset_Object_Settings();
    SDL_DestroyTexture(background_texture);

    return;
}
