#include "../../includes/cub3d.h"

int is_allowed_char(char c)
{
  if(c == ' ' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == 'D')
    return (1);
  return (0);
}

void	init_ptr(t_all **all)
{
	int	i;

	*all = ft_calloc(1, sizeof(t_all));
	(*all)->map = NULL;
	(*all)->infos = NULL;
	(*all)->player_pos.x = 0;
	(*all)->player_pos.y = 0;
	(*all)->player_angle = 0;
	(*all)->starting_dir = 0;
	(*all)->f = 0;
	(*all)->c = 0;
	(*all)->no = 0;
	(*all)->so = 0;
	(*all)->we = 0;
	(*all)->ea = 0;
	(*all)->d = 0;
	(*all)->color_c = 0;
	(*all)->color_f = 0;
	(*all)->wall_img = NULL;
	i = -1;
	while (++i < NB_TEXT)
		(*all)->tab_textures[i] = NULL;
}

int check_format(char *str, char *cmp)
{
  int i;
  int j;

  while(str[i] && ft_strcmp(&str[i], cmp) != 0)
    	i++;
  if(ft_strcmp(&str[i], cmp) == 0)
    return (0);
  return (1);
}