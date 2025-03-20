#include "../../includes/cub3d.h"

void toggle_door(t_all *all)
{
    int map_y;
    int map_x;

    map_y = (all->player_pos.y + (sin(all->player_angle) * TILE_SIZE)) / TILE_SIZE;
    map_x = (all->player_pos.x + (cos(all->player_angle) * TILE_SIZE)) / TILE_SIZE;
    if (all->map[map_y][map_x] == 'D')
        all->map[map_y][map_x] = '6';
    else if (all->map[map_y][map_x] == '6')
        all->map[map_y][map_x] = 'D';
}
