#include "libraries/tools0.h"
#include "libraries/main_program0.h"

int main(int argc, char *argv[])
{
    Global_Variables global_variables;
    init_everything(&global_variables);

    main_program0 main_program(&global_variables);
    main_program.main_menu();

    free_everything(&global_variables);
    return 0;
}
