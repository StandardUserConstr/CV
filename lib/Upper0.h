#ifndef HPP_UPPER0
#define HPP_UPPER0

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


//global var/func
//===============================================================================================
namespace global_variables
{
    const uint32_t SDL_init_flags = SDL_INIT_VIDEO|SDL_INIT_TIMER;
    const uint32_t IMG_init_flags = IMG_INIT_JPG|IMG_INIT_PNG;
}

namespace global_tools
{
    template <typename T> void memset_custom(T* data,const size_t& value,const size_t& count_of_elements) noexcept;
    void const_Cstring_to_array(const char* data_in,char* data_out) noexcept;
    void SDL2_init();
    void IMG_init();
}


//classes
//===============================================================================================
class SDL_TOOLS
{

private:
    uint32_t FpsTimerStart;
    uint32_t FpsTimerEnd;

protected:
    void FpsControl_start() noexcept;
    void FpsControl_end(uint32_t) noexcept;

public:
    void ShowSimpleMessageBox0(Uint32 flags,const char* title,const char* message,const char* StringButton) const noexcept;
    uint8_t Event0() const noexcept;
    virtual ~SDL_TOOLS(){};

};


class Config_SDL_DVD_PROGRAM
{
    #define SIZEOF_FILENAME0_ARRAY 256
protected:
    uint32_t fps;
    char filename0[SIZEOF_FILENAME0_ARRAY];
    SDL_Rect logo_rect0;

public:
    void starting_config() noexcept;
    Config_SDL_DVD_PROGRAM();

    virtual ~Config_SDL_DVD_PROGRAM(){};

};


class SDL_DVD_PROGRAM final : private Config_SDL_DVD_PROGRAM, private SDL_TOOLS
{
    #define SDL_DVD_PROGRAM_WINDOW_W 640
    #define SDL_DVD_PROGRAM_WINDOW_H 480
private:
    bool close;

public:
    SDL_DVD_PROGRAM();
    SDL_DVD_PROGRAM(uint32_t fps,const char filename0[SIZEOF_FILENAME0_ARRAY],SDL_Rect logo_rect0);

    void main_program();

    ~SDL_DVD_PROGRAM(){};

};



#endif
