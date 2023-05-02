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
        perror("in SDL_TextureRectOperations::Paste_texture_To_Renderer_Randomly()\n\
               error: texture_rect_vector.texture.size()!=texture_rect_vector.rect.size()\n");
        return 1;
    }
    if(this->texture_rect_vector.texture.empty()==1)
    {
        perror("in SDL_TextureRectOperations::Paste_texture_To_Renderer_Randomly()\n\
               error: this->texture_rect_vector.texture.empty()==1\n");
        return 1;
    }

    if(change_per_frame==this->variables0.frame)
    {
        this->variables0.frame = 0;
        uint32_t new_texture = rand()%count_of_textures;
        while(new_texture==this->variables0.last_texture) new_texture = rand()%count_of_textures;
        this->variables0.last_texture = new_texture;

        SDL_RenderCopy(render,this->texture_rect_vector.texture[new_texture],NULL,&this->texture_rect_vector.rect[new_texture]);
        return 0;
    }

    variables0.frame++;
    SDL_RenderCopy(render,this->texture_rect_vector.texture[variables0.last_texture],NULL,&this->texture_rect_vector.rect[variables0.last_texture]);

    return 0;
}

uint8_t SDL_TextureRectOperations::Paste_texture_To_Renderer_In_Order_One_Loop(SDL_Renderer* render,uint32_t change_per_frame)
{
    uint32_t count_of_textures = this->texture_rect_vector.texture.size();

    if(this->variables1.actual_sprite==count_of_textures)
    {
        SDL_RenderCopy(render,this->texture_rect_vector.texture[this->variables1.actual_sprite-1],NULL,&this->texture_rect_vector.rect[this->variables1.actual_sprite-1]);
        return 10;
    }

    if(count_of_textures!=this->texture_rect_vector.rect.size())
    {
        perror("in SDL_TextureRectOperations::Paste_texture_To_Renderer_In_Order_One_Loop()\n\
               error: texture_rect_vector.texture.size()!=texture_rect_vector.rect.size()\n");
        return 1;
    }
    if(this->texture_rect_vector.texture.empty()==1)
    {
        perror("in SDL_TextureRectOperations::Paste_texture_To_Renderer_In_Order_One_Loop()\n\
               error: this->texture_rect_vector.texture.empty()==1\n");
        return 1;
    }

    if(change_per_frame==this->variables1.frame)
    {
        this->variables1.frame = 0;
        SDL_RenderCopy(render,this->texture_rect_vector.texture[this->variables1.actual_sprite],NULL,&this->texture_rect_vector.rect[this->variables1.actual_sprite]);
        this->variables1.actual_sprite++;
        if(this->variables1.actual_sprite==count_of_textures) return 10;
        return 0;
    }
    this->variables1.frame++;
    SDL_RenderCopy(render,this->texture_rect_vector.texture[this->variables1.actual_sprite],NULL,&this->texture_rect_vector.rect[this->variables1.actual_sprite]);

    return 0;
}

uint8_t SDL_TextureRectOperations::Change_Specified_texture_In_Opacity_Wave_One_Loop(uint32_t specified_texture_index,double speed = 0.061,double max_speed = 0.4,double min_speed = 0.01,double starting_speed = 0.071)
{
    if(this->variables2.end_loop==1) return 10;
    uint32_t count_of_textures = texture_rect_vector.texture.size();

    if(count_of_textures<specified_texture_index+1)
    {
        perror("in SDL_TextureRectOperations::Change_Specified_texture_In_Opacity_Wave_One_Loop()\n\
               error: index is incorrect (too big)\n");
        return 2;
    }

    /*if(max_speed<1.000)
    {
        perror("in SDL_TextureRectOperations::Change_Specified_texture_In_Opacity_Wave_One_Loop()\n\
               error: max_speed is too small (min 1.000)\n");
        return 2;
    }*/

    if(this->variables2.first_enter==1)
    {
        this->variables2.first_enter = 0;
        SDL_BlendMode blendMode;
        SDL_GetTextureBlendMode(this->texture_rect_vector.texture[specified_texture_index],&blendMode);
        if(blendMode!=SDL_BLENDMODE_BLEND) SDL_SetTextureBlendMode(this->texture_rect_vector.texture[specified_texture_index],SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(this->texture_rect_vector.texture[specified_texture_index],255);

        this->variables2.direction = 0;
        this->variables2.opacity = 255;
        this->variables2.starting_speed = starting_speed;

        return 0;
    }
    if(this->variables2.direction==0)
    {
        this->variables2.opacity-=this->variables2.starting_speed;
        if(this->variables2.opacity<1.000)
        {
            this->variables2.direction = 1;
            this->variables2.opacity = abs(this->variables2.opacity);

        }
        else if(max_speed<this->variables2.starting_speed*speed) this->variables2.starting_speed+=max_speed;
        else this->variables2.starting_speed+=this->variables2.starting_speed*speed;
    }
    else
    {
        if(this->variables2.starting_speed<min_speed) this->variables2.opacity+=min_speed;
        else this->variables2.opacity+=this->variables2.starting_speed;
        if(this->variables2.opacity>=255.000)
        {
            this->variables2.end_loop = 1;
            SDL_SetTextureAlphaMod(this->texture_rect_vector.texture[specified_texture_index],255);
            return 10;

        }
        if(max_speed<this->variables2.starting_speed*speed) this->variables2.starting_speed-=max_speed;
        else this->variables2.starting_speed-=this->variables2.starting_speed*speed;
    }
    //printf("%f\n",this->variables2.opacity);
    /*if(this->variables2.direction==0)
    {
        if(!(this->variables2.might>max_speed)) this->variables2.might+=((this->variables2.might+0.5)*speed);
        else this->variables2.counter++;
        this->variables2.opacity-=this->variables2.might;
        //printf("opacity %d\n",this->variables2.opacity);
        //printf("might %f\n",this->variables2.might);
        if(this->variables2.opacity<=0)
        {
            this->variables2.opacity = abs(this->variables2.opacity);
            //printf("opacity %d ok\n",this->variables2.opacity);
            //printf("might %f ok\n",this->variables2.might);
            this->variables2.might1 = this->variables2.might;
            this->variables2.might = 0.0;
            this->variables2.direction = 1;
        }
    }
    else
    {
        if(this->variables2.counter!=0)
        {
            this->variables2.counter--;
            this->variables2.opacity+=this->variables2.might1;
        }
        else
        {
            this->variables2.might+=((this->variables2.might+0.5)*speed);
            this->variables2.might1-=this->variables2.might;
            if(this->variables2.might1<1.000) this->variables2.might1 = 1.001;
            this->variables2.opacity+=this->variables2.might1;
        }
        //printf("opacity %d\n",this->variables2.opacity);
        //printf("might1 %f\n",abs(this->variables2.might1));
        if(this->variables2.opacity>=255)
        {
            this->variables2.opacity = 255;
            this->variables2.end_loop = 1;
            this->variables2.direction = 0;
            //printf("opacity %d ok\n",this->variables2.opacity);
            //printf("might1 %f ok\n",this->variables2.might1);
            SDL_SetTextureAlphaMod(this->texture_rect_vector.texture[specified_texture_index],this->variables2.opacity);
            return 10;
        }
    */
    SDL_SetTextureAlphaMod(this->texture_rect_vector.texture[specified_texture_index],this->variables2.opacity);

    return 0;
}



bool SDL_TextureRectOperations::Is_Paste_texture_To_Renderer_In_Order_One_Loop_DONE()
{
    if(this->variables1.actual_sprite==this->texture_rect_vector.texture.size()) return 1;
    else return 0;
}

bool SDL_TextureRectOperations::Is_Change_Specified_texture_In_Opacity_Wave_One_Loop_DONE()
{
    if(this->variables2.end_loop==1) return 1;
    else return 0;
}

void SDL_TextureRectOperations::Reset_Paste_texture_To_Renderer_In_Order_One_Loop()
{
    this->variables1.frame = 0;
    this->variables1.actual_sprite = 0;

    return;
}

void SDL_TextureRectOperations::Reset_Change_Specified_texture_In_Opacity_Wave_One_Loop()
{
    this->variables2.first_enter = 1;
    this->variables2.end_loop = 0;

    return;
}


void SDL_TextureRectOperations::Free_Textures_Clear_Rects_Reset_Object_Settings()
{
//Paste_texture_To_Renderer_Randomly
    this->variables0.last_texture = 0;
    this->variables0.frame = 0;

//Paste_texture_To_Renderer_In_Order_One_Loop
    this->variables1.frame = 0;
    this->variables1.actual_sprite = 0;

//Change_Specified_texture_In_Opacity_Wave_One_Loop_variables
    this->variables2.first_enter = 1;
    this->variables2.end_loop = 0;

    uint32_t count_of_textures = this->texture_rect_vector.texture.size();
    for(uint32_t i = 0; i<count_of_textures; i++) SDL_DestroyTexture(this->texture_rect_vector.texture[i]);

    this->texture_rect_vector.texture.clear();
    this->texture_rect_vector.rect.clear();
    return;
}

void SDL_TextureRectOperations::Reset_Object_Settings()
{
//Paste_texture_To_Renderer_Randomly
    this->variables0.last_texture = 0;
    this->variables0.frame = 0;

//Paste_texture_To_Renderer_In_Order_One_Loop
    this->variables1.frame = 0;
    this->variables1.actual_sprite = 0;

//Change_Specified_texture_In_Opacity_Wave_One_Loop_variables
    this->variables2.first_enter = 1;
    this->variables2.end_loop = 0;

    return;
}

void SDL_TextureRectOperations::Update_All_Rects(int16_t x,int16_t y,int16_t w,int16_t h)
{
    uint32_t count_of_textures = this->texture_rect_vector.texture.size();
    for(uint32_t i = 0; i<count_of_textures; i++)
    {
        this->texture_rect_vector.rect[i].x = x;
        this->texture_rect_vector.rect[i].y = y;
        this->texture_rect_vector.rect[i].w = w;
        this->texture_rect_vector.rect[i].h = h;
    }

    return;
}
//===================================================================================================



//EnginePhysics2D_0
//===================================================================================================
uint8_t EnginePhysics2D_0::Change_Specified_rect_Down_Up_Physics_One_Loop(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed = 9.0,double speed = 0.04,int32_t rect_y_where_to_stop = 30)
{
    if(this->variables3.end_loop==1)
    {
        return 10;
    }

    if(speed>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Up_Physics_One_Loop()\n\
               error: speed is too big (max 1.000)\n");
        return 2;
    }

    if(this->variables3.first_enter==1)
    {
        this->variables3.first_enter = 0;

        this->variables3.starting_speed = starting_speed;
        this->variables3.speed = speed;
    }
    if(this->variables3.direction==0)
    {
        *specified_rect_index+=this->variables3.starting_speed;
        this->variables3.starting_speed-=(this->variables3.starting_speed*this->variables3.speed);
        if(this->variables3.starting_speed<1.0) this->variables3.direction = 1;
    }
    else
    {
        *specified_rect_index-=this->variables3.starting_speed;
        if(*specified_rect_index<=rect_y_where_to_stop)
        {
            *specified_rect_index = rect_y_where_to_stop;
            this->variables3.end_loop = 1;
            return 10;
        }
        this->variables3.starting_speed+=(this->variables3.starting_speed*this->variables3.speed);
    }

    return 0;
}

uint8_t EnginePhysics2D_0::Change_Specified_rect_Down_Up_Physics(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed = 8.0,double speed = 0.045,double slow_down_per_hit = 0.9,uint32_t rect_y_where_to_stop =  30)
{
    if(this->variables4.end_loop==1)
    {
        return 10;
    }

    if(speed>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Up_Physics()\n\
               error: speed is too big (max 1.000)\n");
        return 2;
    }

    if(slow_down_per_hit>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Up_Physics()\n\
               error: slow_down_per_hit is too big (max 1.000)\n");
        return 2;
    }


    if(this->variables4.first_enter==1)
    {
        this->variables4.first_enter = 0;

        this->variables4.starting_speed = starting_speed;
        this->variables4.last_starting_speed = starting_speed;
        this->variables4.speed = speed;
        this->variables4.slow_down_per_hit = slow_down_per_hit;
    }
    if(this->variables4.direction==0)
    {
        *specified_rect_index+=this->variables4.starting_speed;
        this->variables4.starting_speed-=(this->variables4.starting_speed*this->variables4.speed);
        if(this->variables4.starting_speed<1.0) this->variables4.direction = 1;
    }
    else
    {
        *specified_rect_index-=this->variables4.starting_speed;
        if(*specified_rect_index<=rect_y_where_to_stop)
        {
            *specified_rect_index = rect_y_where_to_stop;
            this->variables4.direction = 0;

            this->variables4.starting_speed*=this->variables4.slow_down_per_hit;
            if(this->variables4.starting_speed<1.0)
            {
                this->variables4.end_loop = 1;
                return 10;
            }
            return 0;
        }
        if(this->variables4.starting_speed>=this->variables4.last_starting_speed) this->variables4.starting_speed = this->variables4.last_starting_speed;
        else this->variables4.starting_speed+=(this->variables4.starting_speed*this->variables4.speed);
    }

    return 0;
}


uint8_t EnginePhysics2D_0::Change_Specified_rect_Up_Down_Physics_One_Loop(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed = 9.0,double speed = 0.045,int32_t rect_y_where_to_stop = 300)
{
    if(this->variables5.end_loop==1)
    {
        return 10;
    }

    if(speed>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Up_Down_Physics_One_Loop()\n\
               error: speed is too big (max 1.000)\n");
        return 2;
    }

    if(this->variables5.first_enter==1)
    {
        this->variables5.first_enter = 0;

        this->variables5.starting_speed = starting_speed;
        this->variables5.speed = speed;
    }
    if(this->variables5.direction==0)
    {
        *specified_rect_index-=this->variables5.starting_speed;
        this->variables5.starting_speed-=(this->variables5.starting_speed*this->variables5.speed);
        if(this->variables5.starting_speed<1.0) this->variables5.direction = 1;
    }
    else
    {
        *specified_rect_index+=this->variables5.starting_speed;
        if(*specified_rect_index>=rect_y_where_to_stop)
        {
            *specified_rect_index = rect_y_where_to_stop;
            this->variables5.end_loop = 1;
            return 10;
        }
        this->variables5.starting_speed+=(this->variables5.starting_speed*this->variables5.speed);
    }

    return 0;
}


uint8_t EnginePhysics2D_0::Change_Specified_rect_Up_Down_Physics(/*SDL_Renderer* render,*/int* specified_rect_index,double starting_speed = 9.0,double speed = 0.045,double slow_down_per_hit = 0.7,uint32_t rect_y_where_to_stop =  350)
{
    if(this->variables6.end_loop==1)
    {
        return 10;
    }

    if(speed>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Up_Down_Physics()\n\
               error: speed is too big (max 1.000)\n");
        return 2;
    }

    if(slow_down_per_hit>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Up_Down_Physics()\n\
               error: slow_down_per_hit is too big (max 1.000)\n");
        return 2;
    }


    if(this->variables6.first_enter==1)
    {
        this->variables6.first_enter = 0;

        this->variables6.starting_speed = starting_speed;
        this->variables6.last_starting_speed = starting_speed;
        this->variables6.speed = speed;
        this->variables6.slow_down_per_hit = slow_down_per_hit;
    }
    if(this->variables6.direction==0)
    {
        *specified_rect_index-=this->variables6.starting_speed;
        this->variables6.starting_speed-=(this->variables6.starting_speed*this->variables6.speed);
        if(this->variables6.starting_speed<1.0) this->variables6.direction = 1;
    }
    else
    {
        *specified_rect_index+=this->variables6.starting_speed;
        if(*specified_rect_index>=(int32_t)rect_y_where_to_stop)
        {
            *specified_rect_index = rect_y_where_to_stop;
            this->variables6.direction = 0;

            this->variables6.starting_speed*=this->variables6.slow_down_per_hit;
            this->variables6.last_starting_speed = this->variables6.starting_speed;

            if(this->variables6.starting_speed<1.0)
            {
                this->variables6.end_loop = 1;
                return 10;
            }
            return 0;
        }
        if(this->variables6.starting_speed>=this->variables6.last_starting_speed) this->variables6.starting_speed = this->variables6.last_starting_speed;
        else this->variables6.starting_speed+=(this->variables6.starting_speed*this->variables6.speed);
    }

    return 0;
}

uint8_t EnginePhysics2D_0::Change_Specified_rect_Down_Physics_One_Loop(/*SDL_Renderer* render,*/int* specified_rect_index,double weight_of_object = 1.9,double gravity = 9.80,uint32_t rect_y_where_to_stop =  350,uint32_t fps = 60)
{
    if(this->variables7.end_loop==1)
    {
        return 10;
    }

    if(gravity<1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Physics_One_Loop()\n\
               error: gravity is too small (min 1.000)\n");
        return 2;
    }

    if(weight_of_object<0.000001)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Physics_One_Loop()\n\
               error: weight_of_object is too small (min 0.000001)\n");
        return 2;
    }

    this->variables7.time+=1.000/fps;
    *specified_rect_index+=(((this->variables7.time*this->variables7.time)*gravity)+weight_of_object);
    if(*specified_rect_index=rect_y_where_to_stop)
    {
        *specified_rect_index = rect_y_where_to_stop;
        this->variables7.end_loop = 1;
        return 10;
    }


    return 0;
}

uint8_t EnginePhysics2D_0::Change_Specified_rect_Down_Physics(/*SDL_Renderer* render,*/int* specified_rect_index,double weight_of_object = 1.05,double gravity = 9.80,uint32_t rect_y_where_to_stop =  350,double slow_down_per_hit = 0.94,uint32_t fps = 60)
{
    if(this->variables8.end_loop==1)
    {
        return 10;
    }

    if(gravity<0.001)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Physics()\n\
               error: gravity is too small (min 0.001)\n");
        return 2;
    }

    if(weight_of_object<1.000000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Physics()\n\
               error: weight_of_object is too small (min 1.000000)\n");
        return 2;
    }

    if(slow_down_per_hit>1.000)
    {
        perror("in EnginePhysics2D_0::Change_Specified_rect_Down_Physics()\n\
               error: slow_down_per_hit is too bigl (max 1.000)\n");
        return 2;
    }

    if(this->variables8.first_enter==1)
    {
        this->variables8.first_enter = 0;

        this->variables8.weight_of_object = weight_of_object;
        this->variables8.gravity = gravity;
        this->variables8.slow_down_per_hit = slow_down_per_hit;
        this->variables8.rest = 0.0000;
    }

    if(this->variables8.direction==0)
    {
        this->variables8.time+=1.000/fps;
        this->variables8.rest+=(((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)-(int32_t)(((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object);
        if(this->variables8.rest>=1.0000)
        {
            *specified_rect_index+=1;
            this->variables8.rest-=1.0000;
        }
        if((((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)>1.000) *specified_rect_index+=(int32_t)(((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object);
        if(*specified_rect_index>=(int32_t)rect_y_where_to_stop)
        {
            this->variables8.time-=this->variables8.time-(this->variables8.time*this->variables8.slow_down_per_hit);
            this->variables8.direction = 1;
            if(this->variables8.time<=(1.000/fps)*2)
            {
                *specified_rect_index = rect_y_where_to_stop;
                this->variables8.end_loop = 1;
                return 10;

            }
        }
    }
    else
    {
        this->variables8.time-=1.000/fps;
        this->variables8.rest+=((((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)*this->variables8.slow_down_per_hit)-(int32_t)((((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)*this->variables8.slow_down_per_hit);
        if(this->variables8.rest>=1.0000)
        {
            *specified_rect_index-=1;
            this->variables8.rest-=1.0000;
        }
        if((((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)>1.000) *specified_rect_index-=(int32_t)(((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)*this->variables8.slow_down_per_hit;
        if(((((this->variables8.time)*this->variables8.gravity)*this->variables8.weight_of_object)*this->variables8.slow_down_per_hit)<=0.000)
        {
            this->variables8.direction = 0;
            this->variables8.time = 0.000;
            this->variables8.slow_down_per_hit-=this->variables8.slow_down_per_hit/32768;
        }
    }


    return 0;
}

uint8_t EnginePhysics2D_0::Change_Specified_rect_Left_Right_Physics(int* specified_rect_index = 0,double speed_of_slowing_down = 0.995,
                                                                            double starting_speed = 18.0,double slow_down_per_hit = 0.90,int32_t where_is_right_wall = 50,
                                                                            int32_t where_is_left_wall = -10,bool starting_direction = 0,double at_what_speed_stop = 0.05)
{
    if(this->variables9.end_loop==1)
    {
        return 10;
    }

    if(this->variables9.first_enter==1)
    {
        this->variables9.first_enter = 0;

        this->variables9.starting_speed = starting_speed;
        this->variables9.direction = starting_direction;
        this->variables9.rest = 0.000;
    }

    if(this->variables9.direction==0)
    {
        this->variables9.starting_speed*=speed_of_slowing_down;
        this->variables9.rest+=this->variables9.starting_speed-((int32_t)this->variables9.starting_speed);
        if(this->variables9.rest>=1.0000)
        {
            *specified_rect_index+=1;
            this->variables9.rest-=1.0000;
        }
        if(this->variables9.starting_speed>1.0000) *specified_rect_index+=this->variables9.starting_speed;
        if(this->variables9.starting_speed<=at_what_speed_stop)
        {
            this->variables9.end_loop = 1;
            return 10;
        }
        if(*specified_rect_index>=where_is_right_wall)
        {
            this->variables9.direction = 1;
            this->variables9.starting_speed*=slow_down_per_hit;
        }
    }
    else
    {
        this->variables9.starting_speed*=speed_of_slowing_down;
        this->variables9.rest+=this->variables9.starting_speed-((int32_t)this->variables9.starting_speed);
        if(this->variables9.rest>=1.0000)
        {
            *specified_rect_index-=1;
            this->variables9.rest-=1.0000;
        }
        if(this->variables9.starting_speed>1.0000) *specified_rect_index-=this->variables9.starting_speed;
        if(this->variables9.starting_speed<=at_what_speed_stop)
        {
            this->variables9.end_loop = 1;
            return 10;
        }
        if(*specified_rect_index<=where_is_left_wall)
        {
            this->variables9.direction = 0;
            this->variables9.starting_speed*=slow_down_per_hit;
        }
    }


    return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Down_Up_Physics_One_Loop_DONE()
{
    if(this->variables3.end_loop==1) return 1;
    else return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Down_Up_Physics_DONE()
{
    if(this->variables4.end_loop==1) return 1;
    else return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Up_Down_Physics_One_Loop_DONE()
{
    if(this->variables5.end_loop==1) return 1;
    else return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Up_Down_Physics_DONE()
{
    if(this->variables6.end_loop==1) return 1;
    else return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Down_Physics_One_Loop_DONE()
{
    if(this->variables7.end_loop==1) return 1;
    else return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Down_Physics_DONE()
{
    if(this->variables8.end_loop==1) return 1;
    else return 0;
}

bool EnginePhysics2D_0::Is_Change_Specified_rect_Left_Right_Physics_DONE()
{
    if(this->variables9.end_loop==1) return 1;
    else return 0;
}


void EnginePhysics2D_0::Reset_Change_Specified_rect_Down_Up_Physics_One_Loop()
{
    this->variables3.end_loop = 0;
    this->variables3.first_enter = 1;
    this->variables3.direction = 0;

    return;
}

void EnginePhysics2D_0::Reset_Change_Specified_rect_Down_Up_Physics()
{
    this->variables4.end_loop = 0;
    this->variables4.first_enter = 1;
    this->variables4.direction = 0;

    return;
}

void EnginePhysics2D_0::Reset_Change_Specified_rect_Up_Down_Physics_One_Loop()
{
    this->variables5.end_loop = 0;
    this->variables5.first_enter = 1;
    this->variables5.direction = 0;

    return;
}

void EnginePhysics2D_0::Reset_Change_Specified_rect_Up_Down_Physics()
{
    this->variables6.end_loop = 0;
    this->variables6.first_enter = 1;
    this->variables6.direction = 0;

    return;
}

void EnginePhysics2D_0::Reset_Change_Specified_rect_Down_Physics_One_Loop()
{
    this->variables7.end_loop = 0;
    this->variables7.time = 0.000;

    return;
}

void EnginePhysics2D_0::Reset_Change_Specified_rect_Down_Physics()
{
    this->variables8.end_loop = 0;
    this->variables8.time = 0.000;
    this->variables8.first_enter = 1;
    this->variables8.direction = 0;

    return;
}

void EnginePhysics2D_0::Reset_Change_Specified_rect_Left_Right_Physics()
{
    this->variables9.end_loop = 0;
    this->variables9.first_enter = 1;

    return;
}

void EnginePhysics2D_0::Reset_Object_Settings()
{

//Change_Specified_rect_Down_Up_Physics_One_Loop_variables
    this->variables3.end_loop = 0;
    this->variables3.first_enter = 1;
    this->variables3.direction = 0;

//Change_Specified_rect_Down_Up_Physics_variables
    this->variables4.end_loop = 0;
    this->variables4.first_enter = 1;
    this->variables4.direction = 0;

//Change_Specified_rect_Up_Down_Physics_One_Loop_variables
    this->variables5.end_loop = 0;
    this->variables5.first_enter = 1;
    this->variables5.direction = 0;

//Change_Specified_rect_Up_Down_Physics_variables
    this->variables6.end_loop = 0;
    this->variables6.first_enter = 1;
    this->variables6.direction = 0;

//Change_Specified_rect_Down_Physics_One_Loop_variables
    this->variables7.end_loop = 0;
    this->variables7.time = 0.000;

//Change_Specified_rect_Down_Physics_variables
    this->variables8.end_loop = 0;
    this->variables8.time = 0.000;
    this->variables8.first_enter = 1;
    this->variables8.direction = 0;

//Change_Specified_rect_Left_Right_Physics_variables
    this->variables9.end_loop = 0;
    this->variables9.first_enter = 1;

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

void SDL_UniversalTools0::Set_Texture_Opacity_To_Zero_In_Instant(SDL_Texture* texture)
{
    SDL_BlendMode blendMode;
    SDL_GetTextureBlendMode(texture,&blendMode);
    if(blendMode!=SDL_BLENDMODE_BLEND) SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture,0);
    return;
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
    SDL_Surface* CurrentSurf0 = SDL_CreateRGBSurface(0,width,height,16,3840,240,15,61440); //0x0f00 0x00f0 0x000f 0xf000 (it isn't in hex for multiplatform purpouse);
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
