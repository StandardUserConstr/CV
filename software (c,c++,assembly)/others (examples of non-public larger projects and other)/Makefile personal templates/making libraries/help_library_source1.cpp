#include <stdio.h>

//if file exist then 'll return 1; else 'll return 0;
bool Do_file_exist(const char* file)
{
    FILE* file0 = fopen(file,"r");
    if(file0==NULL) return 0;
    fclose(file0);
    return 1;
}

//returns file size
size_t File_size(const char* file_name)
{
    FILE* file0 = fopen(file_name,"r");
	size_t pos0;
	fseek(file0,0,SEEK_END);
	pos0 = ftell(file0);
	fclose(file0);
	return pos0;
}


