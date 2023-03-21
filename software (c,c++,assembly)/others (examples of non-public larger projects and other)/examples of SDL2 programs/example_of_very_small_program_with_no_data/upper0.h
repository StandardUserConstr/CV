#ifndef UPPER0_PROJECT004H
#define UPPER0_PROJECT004H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <stdio.h>

class SDL_UniversalTools;
class SDL_TextureRectOperations;
class UniversalTools;
class SDL_MainProgram;


class SDL_UniversalTools
{

    int32_t FpsControl_FpsTimerEnd;
    uint32_t FpsControl_FpsTimerStart;
    uint8_t FpsControl_fps;

public:
    SDL_UniversalTools(uint32_t fps)
    {
        FpsControl_fps = fps;
    }

    void FpsControl_EndFrame()
    {
        FpsControl_FpsTimerEnd = (FpsControl_FpsTimerStart-SDL_GetTicks());
        if(FpsControl_FpsTimerEnd<0)
        {
            if((1000.0/FpsControl_fps)+FpsControl_FpsTimerEnd<0) return;
            SDL_Delay((1000.0/FpsControl_fps)+FpsControl_FpsTimerEnd);
        }
        else SDL_Delay(1000.0/FpsControl_fps);
        return;
    }

    void FpsControl_StartFrame()
    {
        FpsControl_FpsTimerStart = SDL_GetTicks();
        return;
    }

    uint8_t Change_Texture_Opacity_To_Max(SDL_Texture* texture,uint8_t increase_by)
    {
        SDL_BlendMode blendMode;
        SDL_GetTextureBlendMode(texture,&blendMode);
        if(blendMode!=SDL_BLENDMODE_BLEND) SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
        uint8_t actual_alpha;
        SDL_GetTextureAlphaMod(texture,&actual_alpha);
        if(actual_alpha==255) return 1;
        if((actual_alpha+increase_by)>255)
        {
            increase_by = 0;
            actual_alpha = 255;
        }
        SDL_SetTextureAlphaMod(texture,actual_alpha+increase_by);
        return 0;

    }

    void ShowSimpleMessageBox0(Uint32 flag,const char* title,const char* message,const char* StringButton)
    {
        SDL_MessageBoxButtonData button = {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,0,StringButton};
        SDL_MessageBoxData MsgData =
        {
            flag,
            NULL,
            title,
            message,
            1,
            &button,
            NULL
        };
        int buttonid;
        SDL_ShowMessageBox(&MsgData, &buttonid);
        return;
    }
};


//#include <stdint.h>
//#include <vector>
//#include <time.h>
//#include <stdlib.h>
class SDL_TextureRectOperations
{
    uint32_t Paste_texture_rect_vector_To_Renderer_Randomly_frame;
    uint32_t Paste_texture_rect_vector_To_Renderer_Randomly_last_texture;
    typedef struct TextureRectVector
    {
        std::vector<SDL_Texture*> texture;
        std::vector<SDL_Rect> rect;

    }TextureRectVector;

public:
    SDL_TextureRectOperations()
    {
        Paste_texture_rect_vector_To_Renderer_Randomly_last_texture = 0;
        Paste_texture_rect_vector_To_Renderer_Randomly_frame = 0;
        srand(time(NULL));
    }

    TextureRectVector texture_rect_vector;

    uint8_t Paste_texture_rect_vector_To_Renderer_Randomly(SDL_Renderer* render,uint32_t change_per_frame)
    {
        uint32_t count_of_textures = this->texture_rect_vector.texture.size();

        if(count_of_textures!=this->texture_rect_vector.rect.size())
        {
            perror("in SDL_TextureRectOperations::Paste_texture_rect_vector_To_Renderer_Randomly()\n\
                   error: texture_rect_vector.texture.size()!=texture_rect_vector.rect.size()\n");
            return 1;
        }
        else if(this->texture_rect_vector.texture.empty()==1)
        {
            perror("in SDL_TextureRectOperations::Paste_texture_rect_vector_To_Renderer_Randomly()\n\
                   error: this->texture_rect_vector.texture.empty()==1\n");
            return 1;
        }

        if(change_per_frame==Paste_texture_rect_vector_To_Renderer_Randomly_frame)
        {
            Paste_texture_rect_vector_To_Renderer_Randomly_frame = 0;
            uint32_t new_texture = rand()%count_of_textures;
            while(new_texture==Paste_texture_rect_vector_To_Renderer_Randomly_last_texture) new_texture = rand()%count_of_textures;
            this->Paste_texture_rect_vector_To_Renderer_Randomly_last_texture = new_texture;

            SDL_RenderCopy(render,this->texture_rect_vector.texture[new_texture],NULL,&this->texture_rect_vector.rect[new_texture]);
            return 0;
        }

        Paste_texture_rect_vector_To_Renderer_Randomly_frame++;
        SDL_RenderCopy(render,this->texture_rect_vector.texture[Paste_texture_rect_vector_To_Renderer_Randomly_last_texture],NULL,&this->texture_rect_vector.rect[Paste_texture_rect_vector_To_Renderer_Randomly_last_texture]);

        return 0;
    }


    void Free_Textures_Clear_Rects_Reset_Object_Settings()
    {
        Paste_texture_rect_vector_To_Renderer_Randomly_last_texture = 0;
        Paste_texture_rect_vector_To_Renderer_Randomly_frame = 0;

        uint32_t count_of_textures = this->texture_rect_vector.texture.size();
        for(uint32_t i = 0; i<count_of_textures; i++) SDL_DestroyTexture(this->texture_rect_vector.texture[i]);

        this->texture_rect_vector.texture.clear();
        this->texture_rect_vector.rect.clear();
        return;
    }

};


class UniversalTools
{

public:
    //if function ends success then 'll return 0,else 'll return 1 if "file not exist" or 2 if "reading data error";
    unsigned int Read_from_file(const char* file,uint8_t* data,const size_t read_from_position,const size_t how_many_chars_read)
    {

        FILE* file0 = fopen(file,"r");
        if(file0==NULL) return 1;
        fseek(file0,read_from_position,SEEK_SET);
        size_t result0 = fread(data,sizeof(data[0]),how_many_chars_read,file0);
        fclose(file0);
        if(how_many_chars_read!=result0) return 2;
        return 0;
    }

    //if file exist then 'll return 1; else 'll return 0;
    bool Do_file_exist(const char* file)
    {
        FILE* file0 = fopen(file,"r");
        if(file0==NULL) return 0;
        fclose(file0);
        return 1;
    }

    //returns file size of bytes
    size_t File_size(const char* file_name)
    {
        FILE* file0 = fopen(file_name,"r");
        size_t pos0;
        fseek(file0,0,SEEK_END);
        pos0 = ftell(file0);
        fclose(file0);
        return pos0;
    }

    //if function ends success then 'll return 0,else 1;
    bool Write_to_file(const char* file,const char* data,const bool replace_existing_data)
    {
        size_t size0 = 0;
        FILE* file0;
        if(replace_existing_data) file0 = fopen(file,"w");
        else file0 = fopen(file,"a");
        if(file0==NULL) return 1;
        while(data[size0]!='\0') size0++;  //second initialization size0
        size_t result0 = fwrite(data,sizeof(data[0]),size0,file0);
        fclose(file0);
        if(size0!=result0) return 1;
        return 0;

    }

    //--DANGEROUS
    //if data is the same, then return 0; if not, return 1;
    bool compare_data(uint8_t* data0, uint8_t* data1,size_t sizeof_data0_and_data1)
    {
        for(size_t i = 0; i<sizeof_data0_and_data1; i++) if(data0[i]!=data1[i]) return 1;
        return 0;
    }

    //--DANGEROUS
    //returns count of chars in string (string must have NULL at the end)
    size_t count_string_chars(const char* string_data)
    {
        size_t count_chars = 0;
        for(;; count_chars++) if(string_data[count_chars]=='\0') break;
        return count_chars;
    }

    //--DANGEROUS
    template <typename T> void memset_custom(T* data,const size_t value,const size_t count_of_elements)
    {
        for(size_t i = 0; i<count_of_elements; i++) *(data+i) = value;
        return;
    }
};

class SDL_MainProgram
{

    #define KEY "ro7>%r5=]Egsdgd*T5bf!=bW:k)uDx763gi8W4444fds!.\
~07*)gx@-=J^M>x#:PY#kn0kdsfggt=0M]jwQoNH-sVfX2gK*\
-V6Nv2xF8A2Yri+i_~cJf,)gx@-=J^M>x#:PY#kn0kpMrhQhHPHQ^\
79*FBtZpF#2YX!4)21KtK-isBNd:RE.6FGUmQDT+MqK2AAye>s\
~vKD9tzMp~boeHmnYp!a8D)W?Fqph~boeHmnYp!a8D)W?Fqph"

    SDL_UniversalTools* sdl_universal_tool;
    UniversalTools* universal_tool;

    uint8_t check_key()
    {
        uint32_t length_of_key = universal_tool->count_string_chars(KEY);
        if(universal_tool->Do_file_exist("KEY")==0) return 1;
        if(universal_tool->File_size("KEY")!=length_of_key) return 1;
        uint8_t data[length_of_key+1];
        universal_tool->Read_from_file("KEY",data,0,length_of_key);
        if(universal_tool->compare_data((uint8_t*)KEY,data,length_of_key)==1) return 1;

        return 0;
    }

    void delete_key()
    {
        uint32_t length_of_key = universal_tool->count_string_chars(KEY);
        uint8_t data[length_of_key+1];
        universal_tool->memset_custom(data,'X',length_of_key);
        data[length_of_key] = '\0';
        universal_tool->Write_to_file("KEY",(const char*)data,1);

        return;
    }

protected:
    SDL_Window* window;
    SDL_Renderer* render;
    uint32_t fps;

public:

    uint8_t close_program;
    uint32_t timer_start;

    SDL_MainProgram()
    {

        close_program = 0;
        fps = 60;

        if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
        {
            perror("Initialization SDL2 failed");
            exit(1);
        }
        sdl_universal_tool = new SDL_UniversalTools(fps);
        universal_tool = new UniversalTools();

        if(check_key()==1)
        {
            sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","cannot open this program","ok");
            exit(1);
        }

        window = SDL_CreateWindow("\0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","SDL_CreateWindow failed","ok");
            exit(1);
        }

        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(render==NULL)
        {
            sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","SDL_CreateRenderer failed","ok");
            exit(1);
        }

        Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,1024);



    }

    ~SDL_MainProgram()
    {
        delete this->sdl_universal_tool;
        delete this->universal_tool;
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
    }

    void Event_Standard()
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

    uint8_t Event_0()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    this->close_program = 1;
                break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_b) return 1;
                break;

                default:
                    break;
            }
        }
        return 0;
    }

    void stage_0()
    {
        SDL_TextureRectOperations obj0;
        obj0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"001.png"));
        obj0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"002.png"));
        obj0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"003.png"));
        for(int i = 0; i<obj0.texture_rect_vector.texture.size(); i++)
        {
            if(obj0.texture_rect_vector.texture[i]==NULL)
            {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load some texture/s","ok");
                exit(1);
            }
            SDL_SetTextureBlendMode(obj0.texture_rect_vector.texture[i],SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(obj0.texture_rect_vector.texture[i],0);
        }
        obj0.texture_rect_vector.rect.push_back((SDL_Rect){25,37,326,192});
        obj0.texture_rect_vector.rect.push_back((SDL_Rect){420,240,365,258});
        obj0.texture_rect_vector.rect.push_back((SDL_Rect){26,324,246,240});

        SDL_Texture* texture0 = IMG_LoadTexture(this->render,"000.png");
        if(texture0==NULL)
        {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load 000.png","ok");
                exit(1);
        }
        SDL_Rect rect0 = {0,0,800,600};

        this->timer_start = SDL_GetTicks();
        while(this->close_program!=1)
        {
            sdl_universal_tool->FpsControl_StartFrame();
            SDL_RenderClear(this->render);
            if(SDL_GetTicks()-this->timer_start<16001) this->Event_Standard();
            SDL_RenderCopy(this->render,texture0,NULL,&rect0);
            if(SDL_GetTicks()-this->timer_start>500)
            {
                this->sdl_universal_tool->Change_Texture_Opacity_To_Max(obj0.texture_rect_vector.texture[0],3);
                SDL_RenderCopy(this->render,obj0.texture_rect_vector.texture[0],NULL,&obj0.texture_rect_vector.rect[0]);
            }
            if(SDL_GetTicks()-this->timer_start>6000)
            {
                this->sdl_universal_tool->Change_Texture_Opacity_To_Max(obj0.texture_rect_vector.texture[1],3);
                SDL_RenderCopy(this->render,obj0.texture_rect_vector.texture[1],NULL,&obj0.texture_rect_vector.rect[1]);
            }
            if(SDL_GetTicks()-this->timer_start>16000)
            {
                if(this->Event_0()==1) this->close_program = 1;
                this->sdl_universal_tool->Change_Texture_Opacity_To_Max(obj0.texture_rect_vector.texture[2],3);
                SDL_RenderCopy(this->render,obj0.texture_rect_vector.texture[2],NULL,&obj0.texture_rect_vector.rect[2]);
            }
            SDL_RenderPresent(this->render);
            sdl_universal_tool->FpsControl_EndFrame();
        }
        this->close_program = 0;
        SDL_DestroyTexture(texture0);
        obj0.Free_Textures_Clear_Rects_Reset_Object_Settings();
        return;
    }

    void stage_1()
    {
        this->delete_key();
        SDL_SetWindowSize(this->window,1279,847);
        SDL_SetWindowPosition(this->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
        //SDL_SetWindowFullscreen(this->window,0);

        SDL_TextureRectOperations obj0;
        obj0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"005.png"));
        obj0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"006.png"));
        obj0.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"007.png"));
        for(int i = 0; i<obj0.texture_rect_vector.texture.size(); i++)
        {
            if(obj0.texture_rect_vector.texture[i]==NULL)
            {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load some texture/s","ok");
                exit(1);
            }
        }
        obj0.texture_rect_vector.rect.push_back((SDL_Rect){0,0,1279,728});
        obj0.texture_rect_vector.rect.push_back((SDL_Rect){0,0,1279,728});
        obj0.texture_rect_vector.rect.push_back((SDL_Rect){0,0,1279,728});


        SDL_TextureRectOperations obj1;
        obj1.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"008.png"));
        obj1.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"009.png"));
        obj1.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"010.png"));
        for(int i = 0; i<obj1.texture_rect_vector.texture.size(); i++)
        {
            if(obj1.texture_rect_vector.texture[i]==NULL)
            {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load some texture/s","ok");
                exit(1);
            }
        }
        obj1.texture_rect_vector.rect.push_back((SDL_Rect){511,531,93,172});
        obj1.texture_rect_vector.rect.push_back((SDL_Rect){511,521,92,181});
        obj1.texture_rect_vector.rect.push_back((SDL_Rect){515,532,90,177});

        SDL_TextureRectOperations obj2;
        obj2.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"011.png"));
        obj2.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"012.png"));
        obj2.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"013.png"));
        for(int i = 0; i<obj2.texture_rect_vector.texture.size(); i++)
        {
            if(obj2.texture_rect_vector.texture[i]==NULL)
            {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load some texture/s","ok");
                exit(1);
            }
        }
        obj2.texture_rect_vector.rect.push_back((SDL_Rect){1,469,1278,90});
        obj2.texture_rect_vector.rect.push_back((SDL_Rect){2,469,1274,92});
        obj2.texture_rect_vector.rect.push_back((SDL_Rect){1,462,1275,242});

        SDL_TextureRectOperations obj3;
        obj3.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"014.png"));
        obj3.texture_rect_vector.texture.push_back(IMG_LoadTexture(this->render,"015.png"));
        for(int i = 0; i<obj0.texture_rect_vector.texture.size(); i++)
        {
            if(obj3.texture_rect_vector.texture[i]==NULL)
            {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load some texture/s","ok");
                exit(1);
            }
        }
        obj3.texture_rect_vector.rect.push_back((SDL_Rect){0,0,1279,846});
        obj3.texture_rect_vector.rect.push_back((SDL_Rect){0,0,1279,846});

        SDL_Texture* texture0 = IMG_LoadTexture(this->render,"004.png");
        if(texture0==NULL)
        {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load 000.png","ok");
                exit(1);
        }
        SDL_Rect rect0 = {0,0,1279,847};

        uint32_t frame = 0;
        uint8_t water_texture = 1;
        Mix_Music* music = Mix_LoadMUS("audio.mp3");
        if(music==NULL)
        {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to load audio.mp3","ok");
                exit(1);
        }
        if(Mix_PlayMusic(music,0)==-1)
        {
                this->sdl_universal_tool->ShowSimpleMessageBox0(SDL_MESSAGEBOX_ERROR,"error","Failed to play audio.mp3","ok");
                exit(1);
        }

        while(this->close_program!=1)
        {
            frame++;
            sdl_universal_tool->FpsControl_StartFrame();
            SDL_RenderClear(this->render);
            this->Event_Standard();
            SDL_RenderCopy(this->render,texture0,NULL,&rect0);
            obj1.Paste_texture_rect_vector_To_Renderer_Randomly(this->render,20);
            obj2.Paste_texture_rect_vector_To_Renderer_Randomly(this->render,19);
            obj0.Paste_texture_rect_vector_To_Renderer_Randomly(this->render,5);
            SDL_RenderCopy(this->render,obj3.texture_rect_vector.texture[water_texture],NULL,&obj3.texture_rect_vector.rect[water_texture]);
            if(water_texture==1)
            {
                if((rand()%155)==0) water_texture = 0;
            }
            else if(frame%6==0) water_texture = 1;
            if(frame==10000) frame = 0;

            SDL_RenderPresent(this->render);
            if(Mix_PlayingMusic()==0) close_program = 1;
            sdl_universal_tool->FpsControl_EndFrame();
        }
        this->close_program = 0;
        Mix_FreeMusic(music);
        SDL_DestroyTexture(texture0);
        obj0.Free_Textures_Clear_Rects_Reset_Object_Settings();
        obj1.Free_Textures_Clear_Rects_Reset_Object_Settings();
        obj2.Free_Textures_Clear_Rects_Reset_Object_Settings();
        obj3.Free_Textures_Clear_Rects_Reset_Object_Settings();
        return;
    }
};

#endif

