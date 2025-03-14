#include "../../includes/MLX42/include/MLX42/MLX42.h"
#include "../../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

#define FOV (66 * (M_PI / 180))

// Map
char *map[] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1000001001",
		"1000001001",
		"1111111111"
};

void	refresh_image(mlx_t *mlx, mlx_image_t **image)
{
	if (!*image)
	{
		*image = mlx_new_image(mlx, WIDTH, HEIGHT);
		mlx_image_to_window(mlx, *image, 0, 0);
	}
	else
		ft_bzero((*image)->pixels, WIDTH * HEIGHT);
}


void init_ray(t_all *all, t_raycast *ray, double ray_angle)
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
		ray->dda.side_dist.x = ((all->player_pos.x - (ray->dda.map.x * TILE_SIZE)) / fabs(ray->dda.ray_dir.x));
		ray->step_x = -1;
	}
	else
	{
		ray->dda.side_dist.x = ((ray->dda.map.x + 1) * TILE_SIZE - all->player_pos.x) / fabs(ray->dda.ray_dir.x);
		ray->step_x = 1;
	}
	if (ray->dda.ray_dir.y < 0)
	{
		ray->dda.side_dist.y = ((all->player_pos.y - (ray->dda.map.y * TILE_SIZE)) / fabs(ray->dda.ray_dir.y));
		ray->step_y = -1;
	}
	else
	{
		ray->dda.side_dist.y = ((ray->dda.map.y + 1) * TILE_SIZE - all->player_pos.y) / fabs(ray->dda.ray_dir.y);
		ray->step_y = 1;
	}
}

void draw_wall(t_all *all, t_raycast *ray, int x)
{
	for (int y = 0; y < HEIGHT; y++)
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

void cast_ray(t_all *all, t_raycast *ray, double ray_angle)
{
	// DDA : avancer jusqu’à toucher un mur
	init_ray(all, ray, ray_angle);
	while (map[ray->dda.map.y][ray->dda.map.x] != '1')
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
	if (ray->dda.side == 0)
		ray->perp_wall_dist = (ray->dda.side_dist.x - ray->dda.delta_dist.x);
	else
		ray->perp_wall_dist = (ray->dda.side_dist.y - ray->dda.delta_dist.y);
}

void ray_cast(void *al)
{
	t_all *all = (t_all *)al;
	t_raycast ray;
	refresh_image(all->mlx, &all->wall_img);

	for (int x = 0; x < WIDTH; x++)
	{
		double ray_angle = all->player_angle - (FOV / 2) + ((FOV * x) / WIDTH);
		cast_ray(all, &ray, ray_angle);
		double distance = ray.perp_wall_dist * cos(ray_angle - all->player_angle);

		// Calcul hauteur mur
		ray.wall_height = (int)(TILE_SIZE * HEIGHT / distance);

		// Calcul limites d’affichage du mur
		ray.y_start = (HEIGHT / 2) - (ray.wall_height / 2);
		ray.y_end = (HEIGHT / 2) + (ray.wall_height / 2);
		// Affichage du mur avec une couleur fixe (ex. rouge)
		draw_wall(all, &ray, x);
	}
	mlx_image_to_window(all->mlx, all->wall_img, 0, 0);
	draw_minimap(all);
}

void escape(void *al)
{
	t_all *all = (t_all *)al;
	if (mlx_is_key_down(all->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(all->mlx);
	}
}

int main()
{
	void *mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 0);
	t_all *all;
	all = malloc(sizeof(t_all) * 1);
	all->map = map;
	all->tab_textures[0] = mlx_load_png("/home/vabaud/Documents/Cub3D/textures/W.png");
	all->tab_textures[1] = mlx_load_png("/home/vabaud/Documents/Cub3D/textures/E.png");
	all->tab_textures[2] = mlx_load_png("/home/vabaud/Documents/Cub3D/textures/N.png");
	all->tab_textures[3] = mlx_load_png("/home/vabaud/Documents/Cub3D/textures/S.png");
	all->player_pos.x = 6.5 * TILE_SIZE;
	all->player_pos.y = 2.5 * TILE_SIZE;
	all->player_angle = M_PI / 2; // Angle in degrees
	all->mlx = mlx;
	all->color_f = -10000;
	all->color_c = 10000;
	all->wall_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	all->minimap_img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	if (!mlx)
		return 1;

	mlx_loop_hook(mlx, ray_cast, all);
	mlx_loop_hook(mlx, choice_move, all);
	mlx_loop_hook(mlx, fov_mooves, all);
	mlx_loop_hook(mlx, escape, all);

	mlx_loop(mlx);
	return 0;
}



