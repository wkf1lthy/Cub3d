/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:41:51 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/19 18:42:42 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parsing(t_all **all, int ac, char **av)
{
	check_args(ac, av);
	init_ptr(all);
	fill_tab(all, av[1]);
	check_file(all);
	init_player_position(all);
}
