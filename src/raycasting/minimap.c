#include "../../includes/cub3d.h"

uint32_t	choose_color(char c)
{
	if (c == '0')
		return (0x000000FF);
	else if (c == '1')
		return 0xFFFFFFFF;
    else if (c == 'D')
        return 0x1500FFFF;
    else if (c == '6')
    {
        return 0x5AAAFFFF;
    }
	return 0;
}

void	player_on_minimap(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			mlx_put_pixel(all->minimap_img, (all->player_pos.x / TILE_SIZE * 10)
				+ i, (all->player_pos.y / TILE_SIZE * 10) + j, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_all *all)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = -1;
	refresh_image(all->mlx, &all->minimap_img);
	while (all->map[++y])
	{
		x = -1;
		while (all->map[y][++x])
		{
			i = -1;
			while (++i < 10)
			{
				j = -1;
				while (++j < 10)
				{
					mlx_put_pixel(all->minimap_img, x * 10 + i, y * 10 + j,
						choose_color(all->map[y][x]));
				}
			}
		}
	}
	player_on_minimap(all);
}
