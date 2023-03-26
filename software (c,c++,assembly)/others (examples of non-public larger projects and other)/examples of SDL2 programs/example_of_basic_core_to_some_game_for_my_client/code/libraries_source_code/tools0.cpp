#include "../libraries/tools0.h"

//custom_vector0
//===================================================================================================

//===================================================================================================


//SDL_TextureRectOperations
//===================================================================================================
uint8_t SDL_TextureRectOperations::Paste_texture_To_Renderer_Randomly(SDL_Renderer* render,uint32_t change_per_frame)
{
    uint32_t count_of_textures = this->texture_rect_vector.texture.size();

    if(count_of_textures!=this->texture_rect_vector.rect.size())
    {
        printf_error("in SDL_TextureRectOperations::Paste_texture_To_Renderer_Randomly()\n\
               error: texture_rect_vector.texture.size()!=texture_rect_vector.rect.size()\n");
        return 1;
    }
    else if(this->texture_rect_vector.texture.empty()==1)
    {
        printf_error("in SDL_TextureRectOperations::Paste_texture_To_Renderer_Randomly()\n\
               error: this->texture_rect_vector.texture.empty()==1\n");
        return 1;
    }

    if(change_per_frame==Paste_texture_To_Renderer_Randomly_frame)
    {
        Paste_texture_To_Renderer_Randomly_frame = 0;
        uint32_t new_texture = rand()%count_of_textures;
        while(new_texture==Paste_texture_To_Renderer_Randomly_last_texture) new_texture = rand()%count_of_textures;
        this->Paste_texture_To_Renderer_Randomly_last_texture = new_texture;

        SDL_RenderCopy(render,this->texture_rect_vector.texture[new_texture],NULL,&this->texture_rect_vector.rect[new_texture]);
        return 0;
    }

    Paste_texture_To_Renderer_Randomly_frame++;
    SDL_RenderCopy(render,this->texture_rect_vector.texture[Paste_texture_To_Renderer_Randomly_last_texture],NULL,&this->texture_rect_vector.rect[Paste_texture_To_Renderer_Randomly_last_texture]);

    return 0;
}

void SDL_TextureRectOperations::Reset_Object_Settings()
{
    this->Paste_texture_To_Renderer_Randomly_last_texture = 0;
    this->Paste_texture_To_Renderer_Randomly_frame = 0;
    return;
}


void SDL_TextureRectOperations::Free_Textures_Clear_Rects_Reset_Object_Settings()
{
    this->Paste_texture_To_Renderer_Randomly_last_texture = 0;
    this->Paste_texture_To_Renderer_Randomly_frame = 0;

    uint32_t count_of_textures = this->texture_rect_vector.texture.size();
    for(uint32_t i = 0; i<count_of_textures; i++) SDL_DestroyTexture(this->texture_rect_vector.texture[i]);

    this->texture_rect_vector.texture.clear();
    this->texture_rect_vector.rect.clear();
    return;
}
//===================================================================================================


//SDL_UniversalTools
//===================================================================================================
void SDL_UniversalTools0::FpsControl_EndFrame()
{
    this->FpsControl_FpsTimerEnd = (this->FpsControl_FpsTimerStart-SDL_GetTicks());
    if(this->FpsControl_FpsTimerEnd<0)
    {
        if((1000.0/this->FpsControl_fps)+this->FpsControl_FpsTimerEnd<0) return;
        SDL_Delay((1000.0/this->FpsControl_fps)+this->FpsControl_FpsTimerEnd);
    }
    else SDL_Delay(1000.0/this->FpsControl_fps);
    return;
}

void SDL_UniversalTools0::FpsControl_StartFrame()
{
    FpsControl_FpsTimerStart = SDL_GetTicks();
    return;
}

void SDL_UniversalTools0::change_fps(uint32_t fps)
{
    this->FpsControl_fps = fps;
    return;
}

uint8_t SDL_UniversalTools0::Change_Texture_Opacity_To_Max(SDL_Texture* texture,uint8_t increase_by)
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

void SDL_UniversalTools0::ShowSimpleMessageBox0(Uint32 flag,const char* title,const char* message,const char* StringButton)
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

void SDL_UniversalTools0::ScreenShotJPG(SDL_Renderer* render,const char* filename,int quality,size_t width,size_t height)
{
    SDL_Surface* CurrentSurf0 = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
    SDL_RenderReadPixels(render,NULL,SDL_PIXELFORMAT_UNKNOWN,CurrentSurf0->pixels,CurrentSurf0->pitch);
    IMG_SaveJPG(CurrentSurf0,filename,quality);
    return;
}

void SDL_UniversalTools0::ScreenShotPNG(SDL_Renderer* render,const char* filename,size_t width,size_t height)
{
    SDL_Surface* CurrentSurf0 = SDL_CreateRGBSurface(0,width,height,16,0x0f00,0x00f0,0x000f,0xf000); //that isn`t propably multiplatform scheme (need to be testing);
    SDL_RenderReadPixels(render,NULL,SDL_PIXELFORMAT_ARGB4444,CurrentSurf0->pixels,CurrentSurf0->pitch);
    IMG_SavePNG(CurrentSurf0,filename);
    return;
}
//===================================================================================================


//UniversalTools0
//===================================================================================================
uint8_t UniversalTools0::read_from_file(const char* file,uint8_t* data,const size_t read_from_position,const size_t how_many_chars_read)
{

    FILE* file0 = fopen(file,"rb");
    if(file0==NULL) return 1;
    fseek(file0,read_from_position,SEEK_SET);
    size_t result0 = fread(data,sizeof(data[0]),how_many_chars_read,file0);
    fclose(file0);
    if(how_many_chars_read!=result0) return 2;
    data[result0] = '\0';
    return 0;
}

bool UniversalTools0::do_file_exist(const char* file)
{
    FILE* file0 = fopen(file,"rb");
    if(file0==NULL) return 0;
    fclose(file0);
    return 1;
}
size_t UniversalTools0::file_size(const char* file_name)
{
    FILE* file0 = fopen(file_name,"rb");
    size_t pos0;
    fseek(file0,0,SEEK_END);
    pos0 = ftell(file0);
    fclose(file0);
    return pos0;
}

uint8_t UniversalTools0::write_to_file(const char* file,uint8_t* data,const size_t how_many_chars_write,const size_t write_at_position)
{
    FILE* file0 = fopen(file,"rb+");;
    if(file0==NULL) return 1;
    fseek(file0,write_at_position,SEEK_SET);
    size_t result0 = fwrite(data,1,how_many_chars_write,file0);
    fclose(file0);
    if(how_many_chars_write!=result0) return 2;
    return 0;

}

bool UniversalTools0::compare_data(uint8_t* data0, uint8_t* data1,size_t sizeof_data0_and_data1)
{
    for(size_t i = 0; i<sizeof_data0_and_data1; i++) if(data0[i]!=data1[i]) return 1;
    return 0;
}

size_t UniversalTools0::count_string_chars(const char* string_data)
{
    size_t count_chars = 0;
    for(;; count_chars++) if(string_data[count_chars]=='\0') break;
    return count_chars;
}

template <typename T> void UniversalTools0::memset_custom(T* data,const size_t value,const size_t count_of_elements)
{
    for(size_t i = 0; i<count_of_elements; i++) *(data+i) = value;
    return;
}

//===================================================================================================
