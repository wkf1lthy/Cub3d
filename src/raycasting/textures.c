/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:44:54 by vabaud            #+#    #+#             */
/*   Updated: 2025/03/21 13:45:26 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_wall_face(t_raycast *ray)
{
	if (ray->dda.side == 0)
	{
		if (ray->dda.ray_dir.x < 0)
			ray->wall_face = 2;
		else
			ray->wall_face = 3;
	}
	else
	{
		if (ray->dda.ray_dir.y < 0)
			ray->wall_face = 0;
		else
			ray->wall_face = 1;
	}
}

void	calcul_tex(t_all *all, t_raycast *ray, int y)
{
	double	wall_x;

	if (ray->dda.side == 0)
		wall_x = (all->player_pos.y + ray->perp_wall_dist * ray->dda.ray_dir.y)
			/ TILE_SIZE;
	else
		wall_x = (all->player_pos.x + ray->perp_wall_dist * ray->dda.ray_dir.x)
			/ TILE_SIZE;
	wall_x -= floor(wall_x);
	ray->texture_coord.x = (int)(wall_x
			* (double)all->tab_textures[ray->wall_face]->width);
	ray->texture_coord.y = ((y - ray->y_start)
			* all->tab_textures[ray->wall_face]->height / ray->wall_height);
	if (ray->texture_coord.y >= (int)all->tab_textures[ray->wall_face]->height)
	{
		ray->texture_coord.y = (int)all->tab_textures[ray->wall_face]->height
			- 1;
	}
}

void	calculate_color(mlx_texture_t **texture_tab, t_raycast *ray)
{
	ray->tex_index = ((((int)ray->texture_coord.y
					* (int)texture_tab[ray->wall_face]->width
					+ (int)ray->texture_coord.x))
			* texture_tab[ray->wall_face]->bytes_per_pixel);
	ray->pixel = &texture_tab[ray->wall_face]->pixels[ray->tex_index];
	ray->color = (ray->pixel[0] << 24) | (ray->pixel[1] << 16)
		| (ray->pixel[2] << 8) | ray->pixel[3];
}

void	refresh_image(mlx_t *mlx, mlx_image_t **image)
{
	if (!*image)
	{
		*image = mlx_new_image(mlx, WIDTH, HEIGHT);
		mlx_image_to_window(mlx, *image, 0, 0);
	}
	else
		ft_bzero((*image)->pixels, WIDTH * HEIGHT * 4);
}
