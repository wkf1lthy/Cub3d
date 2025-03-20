/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:35:25 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/20 18:53:02 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_invalid_door(char **map)
{
	size_t	height;
	size_t	i;
	size_t	j;

	height = 0;
	i = 0;
	while (map[height++])
		;
	if (ft_strchr(map[0], 'D') || ft_strchr(map[height - 2], 'D'))
		return (1);
	while (++i < height - 1)
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D' && i > 0 && i < height && (j > ft_strlen(map[i
						- 1]) || j > ft_strlen(map[i + 1])))
				return (1);
		}
		if (map[i][0] == 'D' || map[i][ft_strlen(map[i]) - 1] == 'D')
			return (1);
	}
	return (0);
}

void	check_map_valid(t_all **all)
{
	if (!(*all)->map)
		ft_all_exit(*all, "Map isn't valid");
	if (!forbidden_char((*all)->map))
		ft_all_exit(*all, "wrong char in map");
	if (!is_map_closed((*all)->map))
		ft_all_exit(*all, "Map isn't closed");
	if (!check_start_pos((*all)->map))
		ft_all_exit(*all, "Start position isn't valid");
	if (is_invalid_door((*all)->map))
		ft_all_exit(*all, "they are door on the wall");
}
