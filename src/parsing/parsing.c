#include "../../includes/cub3d.h"

void check_args(int ac, char **av){
    if(ac != 2)
        exit_error("wrong number arguments");
    if(check_format(av[1], ".cub"))
        exit_error("wrong format");   
}

void	check_file(t_all **all)
{
	int	size;

	check_map_valid(all);
	size = -1;
	while ((*all)->infos && (*all)->infos[++size])
		is_info_valid(all, (*all)->infos[size]);
	if (size != NB_TEXT + 2)
		ft_all_exit(*all, "Wrong number of informations");
}


void fill_tab(t_all **all, char *filename)
{
  int		fd;
  int		flag;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_all_exit(*all, "File could not be opened");
	flag = 0;
	adding_line(all, fd, flag);
	close(fd);
}


void init_player_position(t_all **all)
{
   int i;
   int j;
   int found;

   found = 0;
   i = 0;

   while((*all)->map[i])
   {
     j = 0;
     while((*all)->map[i][j])
     {
       if(ft_strchr("NESW", (*all)->map[i][j]))
       {
         if(found)
           ft_all_exit(*all, "Error multiple player positions found");
         init_ptr(all);
         found = 1;
       }
     }
   }
}

void parsing(t_all **all, int ac, char **av){
    check_args(ac, av);
    init_ptr(all);
    fill_tab(all, av[1]);
    check_file(all);
    init_player_position(all);
  }