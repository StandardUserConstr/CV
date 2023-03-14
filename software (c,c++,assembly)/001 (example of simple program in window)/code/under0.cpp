#include "lib/Upper0.h"

//global func
//=============================================================================================================================================

template <typename T> void global_tools::memset_custom(T* data,const size_t& value,const size_t& count_of_elements) noexcept
{
    for(size_t i = 0; i<count_of_elements; i++) *(data+i) = static_cast<T>(value);
    return;
}

void global_tools::const_Cstring_to_array(const char* data_in,char* data_out) noexcept
{
    size_t size_of_Cstring = 0;
    for(;;size_of_Cstring++) if(data_in[size_of_Cstring]=='\0') break;
    for(size_t i = 0; i<size_of_Cstring; i++) data_out[i] = data_in[i];
    data_out[size_of_Cstring] = '\0';

    return;
}


void global_tools::SDL2_init()
{
    if (SDL_Init(global_variables::SDL_init_flags) != 0)
    {
        SDL_TOOLS tool;
        tool.ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","initializing SDL failed","okay");
        throw std::runtime_error("SDL_Init failed");
    }
    return;
}

void global_tools::IMG_init()
{
    if(IMG_Init(global_variables::IMG_init_flags)!=global_variables::IMG_init_flags)
    {
        SDL_TOOLS tool;
        tool.ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","initializing IMG failed","okay");
        throw std::runtime_error("IMG_Init failed");
    }
    return;
}

//SDL func/classes
//=============================================================================================================================================

//keyword "this" is used to define if variable came from class or has been initialized in function;

void Config_SDL_DVD_PROGRAM::starting_config() noexcept
{
    srand(time(NULL));
    this->fps = 30;
    this->logo_rect0.x = rand()%640;
    this->logo_rect0.y = rand()%480;
    this->logo_rect0.w = 136;
    this->logo_rect0.h = 68;
    global_tools::const_Cstring_to_array("dvd.png",this->filename0);
    return;
}

Config_SDL_DVD_PROGRAM::Config_SDL_DVD_PROGRAM()
{
    starting_config();
}

void SDL_TOOLS::ShowSimpleMessageBox0(Uint32 flags,const char* title,const char* message,const char* StringButton) const noexcept
{
        SDL_MessageBoxButtonData button = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,0,StringButton};
        SDL_MessageBoxData MsgData = {
        flags,
        NULL,
        title,
        message,
        1,
        &button,
        NULL};
    int32_t buttonid;
    SDL_ShowMessageBox(&MsgData, &buttonid);
    return;
}

uint8_t SDL_TOOLS::Event0() const noexcept
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return 1;

            default:
                break;
        }
    }
    return 0;
}

void SDL_TOOLS::FpsControl_end(uint32_t fps) noexcept
{
    this->FpsTimerEnd = (this->FpsTimerStart-SDL_GetTicks());
    if(this->FpsTimerEnd<0.0) SDL_Delay((1000.0/fps)+this->FpsTimerEnd);
    else SDL_Delay(1000.0/fps);
    return;
}

void SDL_TOOLS::FpsControl_start() noexcept
{
    this->FpsTimerStart = SDL_GetTicks();
    return;
}

SDL_DVD_PROGRAM::SDL_DVD_PROGRAM(uint32_t fps,const char filename0[SIZEOF_FILENAME0_ARRAY],SDL_Rect logo_rect0)
{
       this->fps = fps;
       this->logo_rect0 = logo_rect0;
       this->close = 0;

       global_tools::memset_custom<char>(this->filename0,'\0',SIZEOF_FILENAME0_ARRAY);

       for(uint32_t i = 0; i<SIZEOF_FILENAME0_ARRAY; i++)
       {
           if(filename0[i]=='\0') break;
           this->filename0[i] = filename0[i];
       }
}

SDL_DVD_PROGRAM::SDL_DVD_PROGRAM()
{
    this->close = 0;
}

void SDL_DVD_PROGRAM::main_program()
{
    if(SDL_WasInit(global_variables::SDL_init_flags)!=global_variables::SDL_init_flags) throw std::runtime_error("SDL has been not initialized flags from variable: global_variable::SDL_init_flags");

    SDL_Window *window0 = SDL_CreateWindow("Corner hits: 0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SDL_DVD_PROGRAM_WINDOW_W,SDL_DVD_PROGRAM_WINDOW_H,0);
    if(window0==NULL) throw std::runtime_error("SDL_CreateWindow failed");

    SDL_Renderer* render0 = SDL_CreateRenderer(window0, -1, SDL_RENDERER_ACCELERATED);
    if(render0==NULL) throw std::runtime_error("SDL_CreateRenderer failed");

    SDL_Surface* surface0 = IMG_Load(this->filename0);
    if(surface0==NULL) throw std::runtime_error("IMG_Load failed");

    SDL_Texture* texture0 = SDL_CreateTextureFromSurface(render0, surface0);
    if(texture0==NULL) throw std::runtime_error("SDL_CreateTextureFromSurface failed");

    SDL_FreeSurface(surface0);


    int x_direction0 = 2;
    int y_direction0 = 2;
    int counter0 = 0;
    std::string chars0 = "Corner hits: 0";

    for(;;)
    {
        this->FpsControl_start();

        if(this->Event0()==1) break; //usually u want to make a switch with more options

        if(this->logo_rect0.x>502)
        {
            if(((this->logo_rect0.x==504)&&(this->logo_rect0.y==412))||((this->logo_rect0.x==504)&&(this->logo_rect0.y==0)))
            {
                counter0 += 1;
                chars0 = "Corner hits: "+std::to_string(counter0);
                SDL_SetWindowTitle(window0,chars0.c_str());
            }
            x_direction0  = -2;
            if(!(this->logo_rect0.x+x_direction0 >502)) SDL_SetTextureColorMod(texture0,rand()%256,rand()%256,rand()%256);
        }
        else if(this->logo_rect0.y>410)
        {
            if(((this->logo_rect0.x==504)&&(this->logo_rect0.y==412))||((this->logo_rect0.x==0)&&(this->logo_rect0.y==412)))
            {
                counter0 += 1;
                chars0 = "Corner hits: "+std::to_string(counter0);
                SDL_SetWindowTitle(window0,chars0.c_str());
            }
            y_direction0 = -2;
            if(!(this->logo_rect0.y+y_direction0>410)) SDL_SetTextureColorMod(texture0,rand()%256,rand()%256,rand()%256);
        }
        else if(this->logo_rect0.x<2)
        {
            SDL_SetTextureColorMod(texture0,rand()%256,rand()%256,rand()%256);
            if(((this->logo_rect0.x==0)&&(this->logo_rect0.y==0))||((this->logo_rect0.x==0)&&(this->logo_rect0.y==412)))
            {
                counter0 += 1;
                chars0 = "Corner hits: "+std::to_string(counter0);
                SDL_SetWindowTitle(window0,chars0.c_str());
            }
            x_direction0  = 2;
        }
        else if(this->logo_rect0.y<2)
        {
            SDL_SetTextureColorMod(texture0,rand()%256,rand()%256,rand()%256);
            if(((this->logo_rect0.x==0)&&(this->logo_rect0.y==0))||((this->logo_rect0.x==504)&&(this->logo_rect0.y==0)))
            {
                counter0 += 1;
                chars0 = "Corner hits: "+std::to_string(counter0);
                SDL_SetWindowTitle(window0,chars0.c_str());
            }
            y_direction0 = 2;
        }
        this->logo_rect0.x += x_direction0;
        this->logo_rect0.y += y_direction0;


        SDL_RenderClear(render0);
        SDL_RenderCopy(render0,texture0,NULL,&this->logo_rect0);
        SDL_RenderPresent(render0);

        this->FpsControl_end(this->fps);
    }


    SDL_DestroyRenderer(render0);
    SDL_DestroyWindow(window0);

    return;
}
