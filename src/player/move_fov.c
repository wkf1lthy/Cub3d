#include "../../includes/cub3d.h"

void rotate_right(t_all *all)
{
	all->player_angle += 0.06;
	if (all->player_angle > 2 * M_PI) // Empêcher un dépassement d'angle
		all->player_angle -= 2 * M_PI;
}

void	rotate_left(t_all *all)
{
	all->player_angle -= 0.06;
	if (all->player_angle < 0)
		all->player_angle += 2 * M_PI;
}

void	fov_mooves(void *param)
{
	t_all	*all;

	all = (t_all *)param;
//	if (all->fov_mouse)
//		return ;
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		rotate_right(all);
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		rotate_left(all);
}