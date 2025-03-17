#include "../../includes/cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_map_closed(char **map)
{
	int	i;
	int	j;
	int	height;
	int	len;

	i = 0;
	while (map[i])
		i++;
	height = i;
	i = -1;
	while (++i < height)
	{
		len = ft_strlen(map[i]);
		j = -1;
		while (++j < len)
		{
			if (!ft_isspace(map[i][j]) && ((is_border(i, j, height, len)
											&& map[i][j] != '1') || (is_allowed_char(map[i][j])
																	 && is_invalid_space(map, i, j, height))))
				return (0);
		}
	}
	return (1);
}


int forbidden_char(char **map)
{
	int i;
	int j;

	i = 0;
	while(map[++i])
	{
		j = 0;
		while(map[i][++j])
		{
			if(!is_allowed_char(map[i][j]) && map[i][j] != '1')
				return(0);
		}
	}
	return(1);
}

int check_start_pos(char **map)
{
	int i;
	int j;
	int start_pos;

	start_pos = 0;
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				start_pos++;
			j++;
		}
		i++;
	}
	return(start_pos == 1);
}

void check_map_valid(t_all **all)
{
	if(!(*all)->map)
		ft_all_exit(*all, "Map isn't valid");
	if(!forbidden_char((*all)->map))
		ft_all_exit(*all, "wrong char in map");
	if(!is_map_closed((*all)->map))
		ft_all_exit(*all, "Map isn't closed");
	if(!check_start_pos((*all)->map))
		ft_all_exit(*all, "Start position isn't valid");
}