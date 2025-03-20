/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:34:36 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/20 18:54:33 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_closed_around(char **map, int i, int j, int height)
{
	if (map[i][j] == '0' && ((i > 0 && j > (int)ft_strlen(map[i - 1]))
			|| (i < height && j > (int)ft_strlen(map[i + 1]))))
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
						&& is_invalid_space(map, i, j, height))
					|| is_closed_around(map, i, j, height)))
				return (0);
		}
	}
	return (1);
}

int	forbidden_char(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_allowed_char(map[i][j]) && map[i][j] != '1'
				&& !ft_isspace(map[i][j]))
				return (0);
		}
	}
	return (1);
}

int	check_start_pos(char **map)
{
	int	i;
	int	j;
	int	start_pos;

	start_pos = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				start_pos++;
		}
	}
	return (start_pos == 1);
}
