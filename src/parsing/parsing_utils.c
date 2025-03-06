#include "../../includes/cub3d.h"

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