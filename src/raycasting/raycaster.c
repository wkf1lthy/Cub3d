#include "../../includes/MLX42/include/MLX42/MLX42.h"
#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592654
#define FOV (66 * (M_PI / 180))
#define TILE_SIZE 64

void *mlx;
mlx_image_t *img;

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

// Player's initial position and angle
double p_x = 6.5 * TILE_SIZE;
double p_y = 2.5 * TILE_SIZE;
double p_angle = M_PI / 2; // Angle in degrees
// Screen dimensions
int s_width = 1000;
int s_height = 800;

void init_ray(t_raycast *ray, double ray_angle)
{
	ray->dda.ray_dir.x = cos(ray_angle);
	ray->dda.ray_dir.y = sin(ray_angle);
	ray->dda.map.x = p_x / TILE_SIZE;
	ray->dda.map.y = p_y / TILE_SIZE;
	ray->dda.delta_dist.x = fabs(TILE_SIZE / ray->dda.ray_dir.x);
	ray->dda.delta_dist.y = fabs(TILE_SIZE / ray->dda.ray_dir.y);
	if (ray->dda.ray_dir.x < 0)
	{
		ray->dda.side_dist.x = ((p_x - (ray->dda.map.x * TILE_SIZE)) / fabs(ray->dda.ray_dir.x));
		ray->step_x = -1;
	}
	else
	{
		ray->dda.side_dist.x = ((ray->dda.map.x + 1) * TILE_SIZE - p_x) / fabs(ray->dda.ray_dir.x);
		ray->step_x = 1;
	}
	if (ray->dda.ray_dir.y < 0)
	{
		ray->dda.side_dist.y = ((p_y - (ray->dda.map.y * TILE_SIZE)) / fabs(ray->dda.ray_dir.y));
		ray->step_y = -1;
	}
	else
	{
		ray->dda.side_dist.y = ((ray->dda.map.y + 1) * TILE_SIZE - p_y) / fabs(ray->dda.ray_dir.y);
		ray->step_y = 1;
	}
}

void draw_wall(int x, int y_start, int y_end)
{
	if (y_start < 0) y_start = 0;            // Empêche les valeurs négatives
	if (y_end > s_height) y_end = s_height;
	for (int y = y_start; y < y_end; y++)
		mlx_put_pixel(img, x, y, 0xFF0000FF);
}

double cast_ray(double ray_angle)
{
	t_raycast ray;
	// DDA : avancer jusqu’à toucher un mur
	init_ray(&ray, ray_angle);
	int side = 0;
	while (map[ray.dda.map.y][ray.dda.map.x] != '1')
	{
		if (ray.dda.side_dist.x < ray.dda.side_dist.y)
		{
			ray.dda.side_dist.x += ray.dda.delta_dist.x;
			ray.dda.map.x += ray.step_x;
			side = 0;
		}
		else
		{
			ray.dda.side_dist.y += ray.dda.delta_dist.y;
			ray.dda.map.y += ray.step_y;
			side = 1;
		}
	}
	if (side == 0)
		return (ray.dda.side_dist.x - ray.dda.delta_dist.x);
	else
		return (ray.dda.side_dist.y - ray.dda.delta_dist.y);
}

int ray_cast()
{
	for (int x = 0; x < s_width; x++)
	{
		double ray_angle = p_angle - (FOV / 2) + ((FOV * x) / s_width);
		double distance = cast_ray((ray_angle));
		distance *= cos(ray_angle - p_angle);

		// Calcul hauteur mur
		int wall_height = (int)(TILE_SIZE * s_height / distance);

		// Calcul limites d’affichage du mur
		int y_start = (s_height / 2) - (wall_height / 2);
		int y_end = (s_height / 2) + (wall_height / 2);

		// Affichage du mur avec une couleur fixe (ex. rouge)
		draw_wall(x, y_start, y_end);
	}
	return 1;
}

void escape(void *all)
{
	(void)all;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
	}
}

int main()
{
	mlx = mlx_init(s_width, s_height, "Cub3D", 0);
	t_all *all;
	all = NULL;
	if (!mlx)
		return 1;

	img = mlx_new_image(mlx, s_width, s_height);
	if (!img)
		return 1;
	ray_cast();
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, escape, all);

	mlx_loop(mlx);
	return 0;
}



