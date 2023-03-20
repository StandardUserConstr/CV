#include "lib/Upper0.h"

int main(int argc, char *argv[])
{
    try
    {
        global_tools::SDL2_init();
        global_tools::IMG_init();
        //SDL_DVD_PROGRAM logo_dvd(60,"dvd.png",{200,300,136,68});
        SDL_DVD_PROGRAM logo_dvd;
        logo_dvd.main_program();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n' << SDL_GetError() << '\n' << IMG_GetError();
        SDL_Quit();
        IMG_Quit();
        return 1;
    }
    SDL_Quit();
    IMG_Quit();

    return 0;
}

