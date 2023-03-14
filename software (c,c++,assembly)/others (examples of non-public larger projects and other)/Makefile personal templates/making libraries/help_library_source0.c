#include <stdio.h>

//if function ends with success then 'll return 0,else 1;
bool Write_to_file(const char* file,const char* data,const bool& replace_existing_data)
{
    size_t size0 = 0;
    FILE* file0;
    if(replace_existing_data) file0 = fopen(file,"w");
    else file0 = fopen(file,"a");
    if(file0==NULL) return 1;
    while(data[size0]!='\0') size0++;
    size_t result0 = fwrite(data,sizeof(data[0]),size0,file0);
    fclose(file0);
    if(size0!=result0) return 1;
    return 0;

}

//if function ends with success then 'll return 0,else 'll return text with error information;
const char* Read_from_file(const char* file,
                           char* data,const size_t& read_from_position,const size_t& how_many_chars_read)
                           {

                               FILE* file0 = fopen(file,"r");
                               if(file0==NULL) return (char*)"FILE_NOT_EXIST\0";
                               fseek(file0,read_from_position,SEEK_SET);
                               size_t result0 = fread(data,sizeof(data[0]),how_many_chars_read,file0);
                               fclose(file0);
                               if(how_many_chars_read!=result0) return (const char*)"READING_DATA_ERROR\0";
                               data[how_many_chars_read] = '\0';
                               return 0;
                           }