#include "../../includes/cub3d.h"

#define MOV_SPEED 5
#define TILE_SIZE 64

void	move_forward(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x + cos(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y + sin(all->player_angle) * MOV_SPEED;
	map_x = (int)((next_x + 5 * cos(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y + 5 * sin(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0' || all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0' || all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	move_backward(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x - cos(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y - sin(all->player_angle) * MOV_SPEED;
	map_x = (int)((next_x - 5 * cos(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y - 5 * sin(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0' || all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0' || all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	move_left(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x - sin(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y + cos(all->player_angle) * MOV_SPEED;
	map_x = (int)((next_x - 5 * sin(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y + 5 * cos(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0' || all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0' || all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	move_right(t_all *all)
{
	double	next_x;
	double	next_y;
	int		map_x;
	int		map_y;

	next_x = all->player_pos.x + sin(all->player_angle) * MOV_SPEED;
	next_y = all->player_pos.y - cos(all->player_angle) * MOV_SPEED;
	map_x = (int)((next_x + 5 * sin(all->player_angle)) / TILE_SIZE);
	map_y = (int)((next_y - 5 * cos(all->player_angle)) / TILE_SIZE);
	if (all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '0' || all->map[map_y][(int)(all->player_pos.x / TILE_SIZE)] == '6')
		all->player_pos.y = next_y;
	if (all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '0' || all->map[(int)(all->player_pos.y / TILE_SIZE)][map_x] == '6')
		all->player_pos.x = next_x;
}

void	choice_move(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (mlx_is_key_down(all->mlx, MLX_KEY_A))
		move_right(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_W))
		move_forward(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_D))
		move_left(all);
	if (mlx_is_key_down(all->mlx, MLX_KEY_S))
		move_backward(all);
}
