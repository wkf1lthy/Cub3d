#include "../../includes/cub3d.h"

void	check_wall_face(t_raycast *raycast)
{
	if (raycast->dda.side == 0)
	{
		if (raycast->dda.ray_dir.x < 0)
			raycast->wall_face = 2;
		else
			raycast->wall_face = 3;
	}
	else
	{
		if (raycast->dda.ray_dir.y < 0)
			raycast->wall_face = 0;
		else
			raycast->wall_face = 1;
	}
}

void	calcul_tex(t_all *all, t_raycast *ray, int y)
{
	double	wall_x;

	if (ray->dda.side == 0)
		wall_x = (all->player_pos.y + ray->perp_wall_dist
									  * ray->dda.ray_dir.y) / TILE_SIZE;
	else
		wall_x = (all->player_pos.x + ray->perp_wall_dist
									  * ray->dda.ray_dir.x) / TILE_SIZE;
	wall_x -= floor(wall_x);
	ray->texture_coord.x = (int)(wall_x
								 * (double)all->tab_textures[ray->wall_face]->width);
	ray->texture_coord.y = ((y - ray->y_start)
							* all->tab_textures[ray->wall_face]->height
							/ ray->wall_height);
	if (ray->texture_coord.y
		>= (int)all->tab_textures[ray->wall_face]->height)
	{
		ray->texture_coord.y
				= (int) all->tab_textures[ray->wall_face]->height - 1;
	}
}

void	calculate_color(mlx_texture_t **texture_tab, t_raycast *raycast)
{
	raycast->tex_index = ((((int)raycast->texture_coord.y
							* (int)texture_tab[raycast->wall_face]->width
							+ (int)raycast->texture_coord.x)
						  ) * texture_tab[raycast->wall_face]->bytes_per_pixel);
	raycast->pixel
			= &texture_tab[raycast->wall_face]->pixels[raycast->tex_index];
	raycast->color = (raycast->pixel[0] << 24) | (raycast->pixel[1] << 16)
					 | (raycast->pixel[2] << 8) | raycast->pixel[3];
}
