#ifndef HELP_LIBRARY_SECURITY_H
#define HELP_LIBRARY_SECURITY_H
#include <stdio.h>

//declarations:
//============================================================================================
bool Write_to_file(const char*,const char*,const bool&);
const char* Read_from_file(const char*,char*,const size_t&,const size_t&);
bool Do_file_exist(const char*);
size_t File_size(const char*);
template <typename T> void memset_custom(T*,const size_t&,const size_t&);
//============================================================================================

#include "help_library_templates0.tpp"
#endif
