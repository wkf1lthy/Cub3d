#include "../../includes/cub3d.h"

int is_allowed_char(char c)
{
  if(c == ' ' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == 'D')
    return (1);
  return (0);
}

char  **add_line(char **map, char *line)
{
  char **new_map;
  int size;
  int i;

  size = 0;
  while(map && map[size])
    size++;
  new_map = ft_calloc(size + 2, sizeof(char *));
  if(!new_map)
    return (NULL);
  i = -1;
  while(++i < size)
    new_map[i] = ft_strdup(map[i]);
  new_map[i++] = ft_strdup(line);
  new_map[i] = NULL;
  free_tab(map);
  return (new_map);
}

int	is_line_map(t_all *all, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == 'N' || line[i] == 'E' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'F' || line[i] == 'C' || line[i] == 'D')
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '\n'
			&& line[i] != 'N' && line[i] != 'D' && line[i] != 'E'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != ' '
			&& line[i] != '\t')
		{
			free(line);
			close(fd);
			ft_all_exit(all, "Forbidden char in map");
		}
		if (line[i + 1] && line[i + 1] == '\n')
			line[i + 1] = '\0';
		i++;
	}
	return (1);
}

void	init_ptr(t_all **all)
{
	int	i;

	*all = ft_calloc(1, sizeof(t_all));
	(*all)->map = NULL;
	(*all)->infos = NULL;
	(*all)->player_pos.x = 0;
	(*all)->player_pos.y = 0;
	(*all)->player_angle = 0;
	(*all)->starting_dir = 0;
	(*all)->f = 0;
	(*all)->c = 0;
	(*all)->no = 0;
	(*all)->so = 0;
	(*all)->we = 0;
	(*all)->ea = 0;
	(*all)->d = 0;
	(*all)->color_c = 0;
	(*all)->color_f = 0;
	(*all)->wall_img = NULL;
	i = -1;
	while (++i < NB_TEXT)
		(*all)->tab_textures[i] = NULL;
}

int check_format(char *str, char *cmp)
{
  int i;

  i = 0;
  while(str[i] && ft_strcmp(&str[i], cmp) != 0)
    	i++;
  if(ft_strcmp(&str[i], cmp) == 0)
    return (0);
  return (1);
}