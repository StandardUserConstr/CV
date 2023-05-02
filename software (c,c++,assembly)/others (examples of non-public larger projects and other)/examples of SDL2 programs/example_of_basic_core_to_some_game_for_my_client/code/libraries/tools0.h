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

    struct TextureRectVector
    {
        custom_vector0<SDL_Texture*> texture;
        custom_vector0<SDL_Rect> rect;

    };


//variables:
    struct Paste_texture_To_Renderer_Randomly_variables
    {
        uint32_t frame;
        uint32_t last_texture;

    }variables0;

    struct Paste_texture_To_Renderer_In_Order_One_Loop_variables
    {
        uint32_t frame;
        uint32_t actual_sprite;

    }variables1;

    struct Change_Specified_texture_In_Opacity_Wave_One_Loop_variables
    {
        bool first_enter;
        bool direction;
        bool end_loop;

        double opacity;
       // double might;
        //double might1;
        //uint32_t counter;
        double starting_speed;

    }variables2;




public:
    static const uint8_t OPERATION_DONE = 10;

    SDL_TextureRectOperations()
    {
        variables0.frame = 0;
        variables0.last_texture = 0;

        variables1.frame = 0;
        variables1.actual_sprite = 0;

        variables2.first_enter = 1;
        variables2.end_loop = 0;

        srand(time(NULL));
    }

    TextureRectVector texture_rect_vector;

    //returns 1 if there's a error;
    uint8_t Paste_texture_To_Renderer_Randomly(SDL_Renderer* render,uint32_t change_per_frame);
    //returns 1 if there's a error; returns 10 if whole operation is done
    uint8_t Paste_texture_To_Renderer_In_Order_One_Loop(SDL_Renderer* render,uint32_t change_per_frame);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //max_speed must be min 1.000
    uint8_t Change_Specified_texture_In_Opacity_Wave_One_Loop(uint32_t specified_texture_index,double speed,double max_speed,double min_speed,double starting_speed);


    //return 0 if not done; return 1 if done;
    bool Is_Paste_texture_To_Renderer_In_Order_One_Loop_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_texture_In_Opacity_Wave_One_Loop_DONE();


    void Reset_Paste_texture_To_Renderer_In_Order_One_Loop();
    void Reset_Change_Specified_texture_In_Opacity_Wave_One_Loop();


    void Free_Textures_Clear_Rects_Reset_Object_Settings();
    void Reset_Object_Settings();

    void Update_All_Rects(int16_t x,int16_t y,int16_t w,int16_t h);

};

class EnginePhysics2D_0
{
    struct Change_Specified_rect_Down_Up_Physics_One_Loop_variables
    {
        bool first_enter;
        bool direction;
        bool end_loop;

        double starting_speed;
        double speed;

    }variables3;

    struct Change_Specified_rect_Down_Up_Physics_variables
    {
        bool first_enter;
        bool direction;
        bool end_loop;
        double slow_down_per_hit;

        double starting_speed;
        double last_starting_speed;
        double speed;

    }variables4;


    struct Change_Specified_rect_Up_Down_Physics_One_Loop_variables
    {
        bool first_enter;
        bool direction;
        bool end_loop;

        double starting_speed;
        //double last_starting_speed;
        double speed;

    }variables5;

    struct Change_Specified_rect_Up_Down_Physics_variables
    {
        bool first_enter;
        bool direction;
        bool end_loop;
        double slow_down_per_hit;

        double starting_speed;
        double last_starting_speed;
        double speed;

    }variables6;

    struct Change_Specified_rect_Down_Physics_One_Loop_variables
    {
        bool end_loop;
        double time;

    }variables7;

    struct Change_Specified_rect_Down_Physics_variables
    {
        bool end_loop;
        double time;
        bool first_enter;
        bool direction;

        double weight_of_object;
        double gravity;
        double slow_down_per_hit;
        double rest;

    }variables8;

    struct Change_Specified_rect_Left_Right_Physics_variables
    {
        bool first_enter;
        bool end_loop;

        bool direction;
        double starting_speed;
        double rest;


    }variables9;

public:
    static const uint8_t OPERATION_DONE = 10;
    EnginePhysics2D_0()
    {
        variables3.end_loop = 0;
        variables3.first_enter = 1;
        variables3.direction = 0;

        variables4.first_enter = 1;
        variables4.direction = 0;
        variables4.end_loop = 0;

        variables5.end_loop = 0;
        variables5.first_enter = 1;
        variables5.direction = 0;

        variables6.first_enter = 1;
        variables6.direction = 0;
        variables6.end_loop = 0;

        variables7.end_loop = 0;
        variables7.time = 0.000;

        variables8.end_loop = 0;
        variables8.time = 0.000;
        variables8.first_enter = 1;
        variables8.direction = 0;

        variables9.first_enter = 1;
        variables9.end_loop = 0;
    }

    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //speed is from 0.0 to 1.0;
    //rect_y_where_to_stop can be changed dynamically
    //specified_rect_index can be changed dynamically
    uint8_t Change_Specified_rect_Down_Up_Physics_One_Loop(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed,double speed,int32_t rect_y_where_to_stop);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //speed is from 0.0 to 1.0;
    //slow_down_per_hit is from 0.0 to 1.0;
    //rect_y_where_to_stop can be changed dynamically
    //specified_rect_index can be changed dynamically
    uint8_t Change_Specified_rect_Down_Up_Physics(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed,double speed,double slow_down_per_hit,uint32_t rect_y_where_to_stop);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //speed is from 0.0 to 1.0;
    //rect_y_where_to_stop can be changed dynamically
    //specified_rect_index can be changed dynamically
    uint8_t Change_Specified_rect_Up_Down_Physics_One_Loop(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed,double speed,int32_t rect_y_where_to_stop);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //speed is from 0.0 to 1.0;
    //slow_down_per_hit is from 0.0 to 1.0;
    //rect_y_where_to_stop can be changed dynamically
    //specified_rect_index can be changed dynamically
    uint8_t Change_Specified_rect_Up_Down_Physics(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed,double speed,double slow_down_per_hit,uint32_t rect_y_where_to_stop);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //rect_y_where_to_stop can be changed dynamically
    //specified_rect_index can be changed dynamically
    uint8_t Change_Specified_rect_Down_Physics_One_Loop(/*SDL_Renderer* render,*/int* specified_rect_index,double weight_of_object,double gravity,uint32_t rect_y_where_to_stop,uint32_t fps);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //slow_down_per_hit is from 0.0 to 1.0;
    //weight_of_object is from 1.0 to upper;
    //gravity is from 0.001 to upper
    //rect_y_where_to_stop can be changed dynamically
    //specified_rect_index can be changed dynamically
    uint8_t Change_Specified_rect_Down_Physics(/*SDL_Renderer* render,*/int* specified_rect_index,double weight_of_object,double gravity,uint32_t rect_y_where_to_stop,double slow_down_per_hit,uint32_t fps);
    //returns 1 or 2 if there's a error; if returns 10 then whole operation is done;
    //speed_of_slowing_down can be changed dynamically
    //slow_down_per_hit can be changed dynamically
    //where_is_right_wall can be changed dynamically
    //where_is_left_wall can be changed dynamically
    //at_what_speed_stop can be changed dynamically
    uint8_t Change_Specified_rect_Left_Right_Physics(int* specified_rect_index,double speed_of_slowing_down,double starting_speed,double slow_down_per_hit,int32_t where_is_right_wall,int32_t where_is_left_wall,bool starting_direction,double at_what_speed_stop);


    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Down_Up_Physics_One_Loop_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Down_Up_Physics_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Up_Down_Physics_One_Loop_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Up_Down_Physics_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Down_Physics_One_Loop_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Down_Physics_DONE();
    //return 0 if not done; return 1 if done;
    bool Is_Change_Specified_rect_Left_Right_Physics_DONE();

    void Reset_Change_Specified_rect_Down_Up_Physics_One_Loop();
    void Reset_Change_Specified_rect_Down_Up_Physics();
    void Reset_Change_Specified_rect_Up_Down_Physics_One_Loop();
    void Reset_Change_Specified_rect_Up_Down_Physics();
    void Reset_Change_Specified_rect_Down_Physics_One_Loop();
    void Reset_Change_Specified_rect_Down_Physics();
    void Reset_Change_Specified_rect_Left_Right_Physics();

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

    void FpsControl_EndFrame();     //add at the end of loop;
    void FpsControl_StartFrame();   //add at the the start of loop;
    void change_fps(uint32_t fps);

    //changes opacity of texture to maximum per loop literals which represents variable "increase_by";
    uint8_t Change_Texture_Opacity_To_Max(SDL_Texture* texture,uint8_t increase_by);
    //setting opacity to zero;
    void Set_Texture_Opacity_To_Zero_In_Instant(SDL_Texture* texture);

    void ShowSimpleMessageBox0(Uint32 flag,const char* title,const char* message,const char* StringButton);

    //[0; 33] is lowest quality,[34; 66] is middle quality,[67; 100] is highest quality;
    void ScreenShotJPG(SDL_Renderer* render,const char* filename,int quality,size_t width,size_t height);
    void ScreenShotPNG(SDL_Renderer* render,const char* filename,size_t width,size_t height);
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
