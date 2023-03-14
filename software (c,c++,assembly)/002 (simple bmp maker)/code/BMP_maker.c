//official compiler options - gcc.exe BMP_maker.c -std=c99 -O2 -s -m32 -static-libgcc -o BMP_maker
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//for_main_program
#include <conio.h>

typedef struct Variables_From_Image_ini
{
    uint16_t width;
    uint16_t height;
    uint8_t* bitmap;
}Variables_From_Image_ini;

void write_bmp(const char* const filename,const uint8_t* const bitmap,const uint16_t width,const uint16_t height);
bool set_variables_from_image_ini(struct Variables_From_Image_ini*);
void memset_custom_UINT8_T(uint8_t* const data,const int value,const size_t count_of_elements);


int main()
{
    Variables_From_Image_ini variable;
    if(set_variables_from_image_ini(&variable)==1)
    {
        getch();
        exit(1);
    }

    write_bmp("file.bmp",variable.bitmap,variable.width,variable.height);

    free(variable.bitmap);
    getch();
    return 0;
}






void write_bmp(const char* const filename,const uint8_t* const bitmap,const uint16_t  width,const uint16_t  height)
{

    const uint32_t bitmap_size =  3 * height * (width+1); //+1 for padding each row

    //54 bytes is weight of template to coding at beginning of file;
//=====================================================================================================
    const uint8_t template0[] = {'B','M'}; //+2bytes (1x1byte and 1x1byte);
    const uint32_t template1[] =
    {
       bitmap_size+54,   //+4bytes (1x4byte) size of the BMP file in bytes;
        0,               //+4bytes (1x4byte) reserved bytes (to skip);
       54,               //+4bytes (1x4byte) starting address of pixel array;
       40,               //+4bytes (1x4byte) size in bytes of this header from this moment to the pixel array;
       width,height      //+8bytes (1x4byte and 1x4byte) width and height of the bitmap;
    };
    const uint16_t template2[] =
    {
        1, //+2bytes (1x2byte) numbers of colors planes (must be 1);
       24  //+2bytes (1x2byte) number of bits per pixel;
    };
    const uint32_t template3[] =
    {
        0,                  //+4bytes (1x4byte) compression method (0 means no compression);
        bitmap_size,        //+4bytes (1x4byte) image size in bytes;
        9006,9006,          //+8bytes (1x4byte and 1x4byte) Dots Per Inch/horizontal and vertical resolution (only matter for printing so i use default parameters);
        0,                  //+8bytes number of colors in the color palette (0 stands for deafult);
        24                  //+8bytes number of important colors used or 0 when every color is important;
    };
//=====================================================================================================
    FILE* fp = fopen(filename,"wb");
    fwrite(template0, sizeof(template0),1,fp);
    fwrite(template1, sizeof(template1),1,fp);
    fwrite(template2, sizeof(template2),1,fp);
    fwrite(template3, sizeof(template3),1,fp);

    fwrite(bitmap,height*width*3,1,fp);
    fclose(fp);
    printf("\n\n  File created");   //delete for performance
    return;
}



bool set_variables_from_image_ini(struct Variables_From_Image_ini* variable)
{
    FILE* fp = fopen("image.ini", "rb");
    const char* error ;
    while(1)
    {
        if(fp==NULL)
        {
            error = "file \"image.ini\" doesn't exist\0";
            break;
        }

        uint8_t width[13];
        uint8_t height[14];
        uint8_t image_width[5];
        memset_custom_UINT8_T(image_width,'\0',5);
        uint8_t image_height[5];
        memset_custom_UINT8_T(image_height,'\0',5);
        fseek(fp,7,SEEK_SET);
        for(uint8_t i = 0; i<6; i++)
        {
            if(i==5)
            {
                memset_custom_UINT8_T(image_width,4,5);
                break;
            }
            width[i] = fgetc(fp);
            if(width[i]==13)
            {
                width[i] = '\0';
                break;
            }
            image_width[i] = width[i];
        }
        fseek(fp,9,SEEK_CUR);
        const int32_t image_width_number = atoi((const char*)image_width);

        for(uint8_t i = 0; i<6; i++)
        {
            if(i==5)
            {
                memset_custom_UINT8_T(image_height,4,5);
                break;
            }
            height[i] = fgetc(fp);
            if(height[i]==13)
            {
                height[i] = '\0';
                break;
            }
            image_height[i] = height[i];
        }

        const int32_t image_height_number = atoi((const char*)image_height);

        if(image_width_number > 21843 || image_width_number < 1)
        {
            error = "\n\n  width is too big or too small incorrect\0";
            break;
        }
        if(image_height_number > 21843 || image_height_number < 1)
        {
            error = "\n\n  height is too big or too small or incorrect\0";
            break;
        }

        //size_t const array_size = image_height_number*image_width_number*3;
        variable->bitmap = (uint8_t*)malloc(image_height_number*image_width_number*3);
        uint8_t buffor[4];
        memset_custom_UINT8_T(buffor,'\0',4);
        uint8_t buffor1[4];
        memset_custom_UINT8_T(buffor1,'\0',4);
        uint8_t k = 0;
        bool repeat_loop_k = 1;
        for(size_t i = 0; ; i++)
        {
            memset_custom_UINT8_T(buffor,'\0',3);
            memset_custom_UINT8_T(buffor1,'\0',3);
            buffor[0] = fgetc(fp);
            if(buffor[0]=='/') break;
            if(buffor[0]>47&&buffor[0]<58)
            {
                for(k = 0; k<2; k++)
                {
                    buffor1[k] = buffor[k];
                    buffor[k+1] = fgetc(fp);
                    if(buffor[k+1]>47&&buffor[k+1]<58) continue;
                    else repeat_loop_k = 0;
                    if(repeat_loop_k==0)
                    {
                        variable->bitmap[i] = atoi((const char*)buffor1);
                        printf("0x%02X|",atoi((const char*)buffor1));          //delete for performance
                        break;
                    }
                }
                if(repeat_loop_k==1)
                {
                    variable->bitmap[i] = atoi((const char*)buffor);
                    printf("0x%02X|",atoi((const char*)buffor));      //delete for performance
                }
                else repeat_loop_k = 1;
            }
            else
            {
                i--;
                continue;
            }
        }

        fclose(fp);
        variable->height = image_height_number;
        variable->width = image_width_number;

        //reverse array
        //----------------------
      /*uint8_t* array_reverse = (uint8_t*)malloc(array_size);
        size_t i;
        for (i = 0; i < array_size; i++) array_reverse[array_size - 1 - i] = variable->bitmap[i];
        for (i = 0; i < array_size; i++) variable->bitmap[i] = array_reverse[i];
        free(array_reverse);*/
        //----------------------
        return 0;
    }

    printf("%s",error);
    fclose(fp);
    return 1;
}

void memset_custom_UINT8_T(uint8_t* data,const int value,const size_t count_of_elements)
{
    for(size_t i = 0; i<count_of_elements; i++) *(data+i) = value;
    return;
}
