/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:57:32 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/20 19:04:13 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_all	*all;

	parsing(&all, ac, av);
	all->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	mlx_loop_hook(all->mlx, ray_cast, all);
	mlx_loop_hook(all->mlx, choice_move, all);
	mlx_loop_hook(all->mlx, fov_mooves, all);
	mlx_loop_hook(all->mlx, escape, all);
	mlx_key_hook(all->mlx, toggle, all);
	mlx_loop(all->mlx);
	return (0);
}
