#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>                      //IMG_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define printf_error(string) fprintf(stderr,string)
#define printf_error_args(string,args) fprintf(stderr,string,args)

template <typename T> class custom_vector0;     //dynamic object
class SDL_TextureRectOperations;                //dynamic object

class SDL_UniversalTools0;
class UniversalTools0;

//#include <stdlib.h>
template <typename T> class custom_vector0
{

    T* main_data;
    size_t element_count;
    size_t size_of_obiekt;

public:
    custom_vector0()
    {
        this->main_data = (T*)malloc(sizeof(T)*4);
        this->element_count = 0;
        this->size_of_obiekt = sizeof(T)*4;
    }

    void clear()
    {
        if(this->size_of_obiekt==0) return;
        this->element_count = 0;
        this->size_of_obiekt = sizeof(T)*4;
        free(this->main_data);
        this->main_data = (T*)malloc(sizeof(T)*4);
        return;
    }

    void push_back(T variable)
    {
        this->element_count++;
        if(this->element_count%4==0)
        {
            T* copy_data = (T*)malloc((sizeof(T)*(this->element_count*2)));
            size_t i;
            for(i = 0; i<this->element_count-1; i++) copy_data[i] = this->main_data[i];


            free(this->main_data);
            this->main_data = (T*)malloc((sizeof(T)*(this->element_count*2)));
            for(i = 0; i<this->element_count-1; i++) this->main_data[i] = copy_data[i];
            free(copy_data);

            this->size_of_obiekt = (sizeof(T)*(this->element_count*2));
        }
         this->main_data[this->element_count-1] = variable;
    }

    void pop_back()
    {
        this->main_data[this->element_count-1] = (T)NULL;
        this->element_count--;
        return;
    }

    size_t size()
    {
        return this->element_count;
    }

    size_t real_size_in_bytes()
    {
        return this->size_of_obiekt;
    }

    size_t size_of_elements_in_bytes()
    {
        return this->element_count*sizeof(T);
    }

    bool empty()
    {
        return 1 ? this->element_count == 0 : 0;
    }

    T& operator[](const size_t iterator)
    {
        return this->main_data[iterator];
    }

    ~custom_vector0()
    {
        if(this->size_of_obiekt!=0) free(this->main_data);
    }

};

//#include <stdint.h>
//#include <time.h>
//#include <stdlib.h>
class SDL_TextureRectOperations
{

    typedef struct TextureRectVector
    {
        custom_vector0<SDL_Texture*> texture;
        custom_vector0<SDL_Rect> rect;

    }TextureRectVector;

    uint32_t Paste_texture_To_Renderer_Randomly_frame;
    uint32_t Paste_texture_To_Renderer_Randomly_last_texture;

public:
    SDL_TextureRectOperations()
    {
        Paste_texture_To_Renderer_Randomly_last_texture = 0;
        Paste_texture_To_Renderer_Randomly_frame = 0;
        srand(time(NULL));
    }

    TextureRectVector texture_rect_vector;

    uint8_t Paste_texture_To_Renderer_Randomly(SDL_Renderer* render,uint32_t change_per_frame);

    void Free_Textures_Clear_Rects_Reset_Object_Settings();
    void Reset_Object_Settings();

};

//#include <stdint.h>
//#include <SDL2/SDL.h>
class SDL_UniversalTools0
{

    int32_t FpsControl_FpsTimerEnd;
    uint32_t FpsControl_FpsTimerStart;
    uint8_t FpsControl_fps;

public:
    SDL_UniversalTools0(uint32_t fps)
    {
        this->FpsControl_fps = fps;
    }

    void FpsControl_EndFrame();   //add at the end of loop
    void FpsControl_StartFrame();   //add at the the start of loop
    void change_fps(uint32_t fps);

    //changes opacity of texture to maximum per loop literals which represents variable "increase_by"
    uint8_t Change_Texture_Opacity_To_Max(SDL_Texture* texture,uint8_t increase_by);

    void ShowSimpleMessageBox0(Uint32 flag,const char* title,const char* message,const char* StringButton);

    //[0; 33] is lowest quality,[34; 66] is middle quality,[67; 100] is highest quality;
    void ScreenShotJPG(SDL_Renderer* render,const char* filename,int quality,size_t width,size_t height);
    void ScreenShotPNG(SDL_Renderer* render,const char* filename,size_t width,size_t height);        //something need to be tested for multiplatform issues
};

//#include <stdio.h>
//#include <stdint.h>
class UniversalTools0
{

public:
    //--DANGEROUS
    //if function ends success then 'll return 0,else 'll return 1 if "file not exist" or 2 if "reading data error";
    //"data" variable must be 1 byte longer 'cause of '\0' that 'll be added at the end;
    uint8_t read_from_file(const char* file,uint8_t* data,const size_t read_from_position,const size_t how_many_chars_read);

    //if file exist then 'll return 1; else 'll return 0;
    bool do_file_exist(const char* file);

    //returns file size in bytes
    size_t file_size(const char* file_name);

    //--DANGEROUS
    //if function ends success then 'll return 0,else if file not exist returns 1,else if writing failed returns 2;
    uint8_t write_to_file(const char* file,uint8_t* data,const size_t how_many_chars_write,const size_t write_at_position);

    //--DANGEROUS
    //if data is the same, then return 0; if not, return 1;
    bool compare_data(uint8_t* data0, uint8_t* data1,size_t sizeof_data0_and_data1);

    //--DANGEROUS
    //returns count of chars in string without '\0' (string must have NULL at the end)
    size_t count_string_chars(const char* string_data);

    //--DANGEROUS
    template <typename T> void memset_custom(T* data,const size_t value,const size_t count_of_elements);
};
