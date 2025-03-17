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
    {
          is_info_valid(all, (*all)->infos[size]);
    }
	if (size != NB_TEXT + 1)
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

void	init_player(t_all **all, int i, int j)
{
	(*all)->player_pos.x = (j + 0.5) * TILE_SIZE;
	(*all)->player_pos.y = (i + 0.5) * TILE_SIZE;
	(*all)->starting_dir = (*all)->map[i][j];
	if ((*all)->map[i][j] == 'N')
		(*all)->player_angle = 3 * M_PI / 2;
	else if ((*all)->map[i][j] == 'E')
		(*all)->player_angle = 0;
	else if ((*all)->map[i][j] == 'S')
		(*all)->player_angle = M_PI / 2;
	else if ((*all)->map[i][j] == 'W')
		(*all)->player_angle = M_PI;
	(*all)->map[i][j] = '0';
}

void init_player_position(t_all **all)
{
   int i;
   int j;
   int found;

   found = 0;
   i = -1;

   while((*all)->map[++i])
   {
     j = -1;
     while((*all)->map[i][++j])
     {
       if(ft_strchr("NESW", (*all)->map[i][j]))
       {
         if(found)
           ft_all_exit(*all, "Error multiple player positions found");
         init_player(all, i, j);
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