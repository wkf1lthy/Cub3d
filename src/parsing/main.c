#include "../../includes/cub3d.h"


int main(int ac, char **av){
    t_all *all;

    init_ptr(&all);
    parsing(&all, ac, av);
    return(0);
}