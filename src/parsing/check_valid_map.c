/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:35:25 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/19 18:42:28 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
}
