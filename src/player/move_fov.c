#include "../../includes/cub3d.h"

void	cursor_move(double x_pos, double y_pos, void *param)
{
	t_all	*all;

	all = (t_all *)param;
    if (!all->fov_mouse)
        return;
    (void)y_pos;
	if (x_pos > all->last_cursor_x)
		all->player_angle += 0.04;
	else if (x_pos < all->last_cursor_x)
		all->player_angle -= 0.04;
	all->last_cursor_x = x_pos;
}

void toggle(mlx_key_data_t keydata, void *param)
{
    t_all *all;
    all = (t_all *)param;
	int y = 0;

    if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
    {
        toggle_door(all);
    }
    if (!all->fov_mouse && keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_F)
	{
		mlx_set_cursor_mode(all->mlx, MLX_MOUSE_DISABLED);
		all->fov_mouse = 1;
		mlx_get_mouse_pos(all->mlx, &all->last_cursor_x, &y);
		mlx_cursor_hook(all->mlx, cursor_move, all);
	}
	else if (all->fov_mouse && keydata.action == MLX_RELEASE && keydata.key == MLX_KEY_F)
	{
		mlx_set_cursor_mode(all->mlx, MLX_MOUSE_NORMAL);
		all->fov_mouse = 0;
	}
}

void	fov_mooves(void *param)
{
	t_all *all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_RIGHT))
		all->player_angle += 0.06;
	else if (mlx_is_key_down(all->mlx, MLX_KEY_LEFT))
		all->player_angle -= 0.06;
}