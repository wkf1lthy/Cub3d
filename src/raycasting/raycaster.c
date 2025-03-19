#include "../../includes/cub3d.h"

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

void	init_ray(t_all *all, t_raycast *ray, double ray_angle)
{
	ray->dda.ray_dir.x = cos(ray_angle);
	ray->dda.ray_dir.y = sin(ray_angle);
	ray->dda.map.x = all->player_pos.x / TILE_SIZE;
	ray->dda.map.y = all->player_pos.y / TILE_SIZE;
	ray->dda.delta_dist.x = fabs(TILE_SIZE / ray->dda.ray_dir.x);
	ray->dda.delta_dist.y = fabs(TILE_SIZE / ray->dda.ray_dir.y);
	ray->dda.side = 0;
	if (ray->dda.ray_dir.x < 0)
	{
		ray->dda.side_dist.x = ((all->player_pos.x - (ray->dda.map.x
						* TILE_SIZE)) / fabs(ray->dda.ray_dir.x));
		ray->step_x = -1;
	}
	else
	{
		ray->dda.side_dist.x = ((ray->dda.map.x + 1) * TILE_SIZE
				- all->player_pos.x) / fabs(ray->dda.ray_dir.x);
		ray->step_x = 1;
	}
	if (ray->dda.ray_dir.y < 0)
	{
		ray->dda.side_dist.y = ((all->player_pos.y - (ray->dda.map.y
						* TILE_SIZE)) / fabs(ray->dda.ray_dir.y));
		ray->step_y = -1;
	}
	else
	{
		ray->dda.side_dist.y = ((ray->dda.map.y + 1) * TILE_SIZE
				- all->player_pos.y) / fabs(ray->dda.ray_dir.y);
		ray->step_y = 1;
	}
}

void	draw_wall(t_all *all, t_raycast *ray, int x)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y < ray->y_start)
			mlx_put_pixel(all->wall_img, x, y, all->color_c);
		else if (y > ray->y_end)
			mlx_put_pixel(all->wall_img, x, y, all->color_f);
		else
		{
			calcul_tex(all, ray, y);
			calculate_color(all->tab_textures, ray);
			mlx_put_pixel(all->wall_img, x, y, ray->color);
		}
	}
}

void	dda(t_all *all, t_raycast *ray, double ray_angle)
{
	init_ray(all, ray, ray_angle);
	while (all->map[ray->dda.map.y][ray->dda.map.x] != '1'
		&& all->map[ray->dda.map.y][ray->dda.map.x] != 'D')
	{
		if (ray->dda.side_dist.x < ray->dda.side_dist.y)
		{
			ray->dda.side_dist.x += ray->dda.delta_dist.x;
			ray->dda.map.x += ray->step_x;
			ray->dda.side = 0;
		}
		else
		{
			ray->dda.side_dist.y += ray->dda.delta_dist.y;
			ray->dda.map.y += ray->step_y;
			ray->dda.side = 1;
		}
	}
	check_wall_face(ray);
    if (all->map[ray->dda.map.y][ray->dda.map.x] == 'D')
    {
        ray->wall_face = 4;
    }
	if (ray->dda.side == 0)
		ray->perp_wall_dist = (ray->dda.side_dist.x - ray->dda.delta_dist.x);
	else
		ray->perp_wall_dist = (ray->dda.side_dist.y - ray->dda.delta_dist.y);
}

void	ray_cast(void *param)
{
	t_all		*all;
	int			x;
	t_raycast	ray;
	double		ray_angle;
	double		distance;

	all = (t_all *)param;
	x = -1;
	refresh_image(all->mlx, &all->wall_img);
	while (++x < WIDTH)
	{
		ray_angle = all->player_angle - (FOV / 2) + ((FOV * x) / WIDTH);
		dda(all, &ray, ray_angle);
		distance = ray.perp_wall_dist * cos(ray_angle - all->player_angle);
		ray.wall_height = (int)(TILE_SIZE * HEIGHT / distance);
		ray.y_start = (HEIGHT / 2) - (ray.wall_height / 2);
		ray.y_end = (HEIGHT / 2) + (ray.wall_height / 2);
		draw_wall(all, &ray, x);
	}
	draw_minimap(all);
}

void	escape(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(all->mlx);
	}
}
