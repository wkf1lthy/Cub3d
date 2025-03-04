#include "cube3d.h"

void check_args(int ac, char **av){
    if(ac != 2)
        exit_error("wrong number arguments");
    if(check_format(av[1], .cub));
        exit_error("wrong format");   
}

