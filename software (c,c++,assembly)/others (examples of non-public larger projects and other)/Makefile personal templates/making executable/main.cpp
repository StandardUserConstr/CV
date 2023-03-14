#include "help_library.h"
int main()
{
    printf("\nprogram zostal uruchomiony\n");

    const char* file_name = "plik.txt";
	if(Do_file_exist(file_name)==true)
	{
		bool result0 = Write_to_file(file_name,"tekst ktory podaje plikowi",0); //change to: 1 if u want to clear file before write;
		if(result0==1) perror("ERROR");

		char text_from_file0[30];
		memset_custom(text_from_file0,'\0',sizeof(text_from_file0)); 

		const char* error0 = Read_from_file(file_name,text_from_file0,0,26);
		if(error0!=0) perror(error0);
		else printf("%s\n",text_from_file0);

	}
	else printf("\nplik nie istnieje");

	return 0;

}
