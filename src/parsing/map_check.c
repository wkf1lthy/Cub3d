#include "../../includes/cub3D.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_map_closed(char **map)
{
  int	i;
  int	j;
  int	height;
  int	len;

  height = get_map_height(map);
  i = 0;
  while (i < height)
  {
    len = ft_strlen(map[i]);
    j = 0;
    while (j < len)
    {
      if ((is_border(i, j, height, len) && map[i][j] != '1')
        || (!is_border(i, j, height, len)
          && (!is_allowed_char(map[i][j])
          || (map[i][j] == '0' && is_invalid_space(map, i, j)))))
        return (0);
      j++;
    }
    i++;
  }
  return (1);
}