/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:34:36 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/20 17:34:42 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_map_closed(char **map)
{
	int		i;
	int		height;
	size_t	max_len;
	size_t	len;

	i = 0;
	while (map[i])
		i++;
	height = i;
	max_len = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (mapping(map, max_len, height));
}

int	mapping(char **map, size_t max_len, int height)
{
	int		i;
	size_t	j;

	i = 0;
	while (++i < height)
	{
		j = 0;
		while (++j < max_len)
		{
			if (j >= ft_strlen(map[i]))
			{
				if (is_border(i, j, height, max_len) && map[i][j] != '1')
					return (0);
			}
			else if (!ft_isspace(map[i][j]) && ((is_border(i, j, height,
							max_len) && map[i][j] != '1' && map[i][j] != 'D')
					|| (is_allowed_char(map[i][j]) && is_invalid_space(map, i,
							j, height))))
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