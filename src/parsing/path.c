#include "../../includes/cub3d.h"

int valid_path(char *path, t_all **all, int index)
{
  char *str;
  int fd;

  str = ft_strtrim(path, "\n ");
  if(!str)
    return(0);
  if(ft_strlen(str) < 4 || ft_strcmp(str + ft_strlen(str) - 4, ".png") != 0)
      return(free(str), 0);
  fd = open(path, O_RDONLY);
  if(fd == -1)
    return(free(str), 0);
  close(fd);
  (*all)->tab_textures[index] = mlx_load_png(str);
  free(str);
  if(!(*all)->tab_textures[index])
    return(0);
  return(1);
}

void	update_count(t_all **all, char *id)
{
  if (ft_strcmp(id, "NO ") == 0)
    (*all)->no += 1;
  else if (ft_strcmp(id, "SO ") == 0)
    (*all)->so += 1;
  else if (ft_strcmp(id, "WE ") == 0)
    (*all)->we += 1;
  else if (ft_strcmp(id, "EA ") == 0)
    (*all)->ea += 1;
  else if (ft_strcmp(id, "F ") == 0)
    (*all)->f += 1;
  else if (ft_strcmp(id, "C ") == 0)
    (*all)->c += 1;
  if ((*all)->c > 1 || (*all)->f > 1 || (*all)->no > 1 || (*all)->so > 1
    || (*all)->we > 1 || (*all)->ea > 1)
    ft_all_exit(*all, "Infos are existing more than one time");
}

int id_line(char *line, t_all **all, int i)
{
  char *id[5];
  int k;
  int j;
  id[0] = "NO ";
  id[1] = "SO ";
  id[2] = "WE ";
  id[3] = "EA ";

  while(++i < 5)
  {
    k = -1;
    while(line[k] && line[k] == ' ')
      k++;
    j = -1;
    while(id[i][++j] && line &&  i < 3)
      if(id[i][j] != line[k++])
         break ;
    if(j == 3)
      break ;
  }
  if(i == 4)
    return(1);
  update_count(all, id[i]);
  return(0);
}

int get_line(char *line)
{
  int i;

  i = 0;
  while(line[i] && line[i] == ' ')
    i++;
  if(line[i] == 'N')
    return(0);
  else if(line[i] == 'S')
    return(1);
  else if(line[i] == 'W')
    return(2);
  else if(line[i] == 'E')
    return(3);
  return(-1);
}

int is_info_valid(t_all **all, char *line)
{
  int i;

  i = -1;
  while(line[++i] && line[i] == ' ')
    continue;
  if(!id_line(line, all, -1))
  {
    if(!valid_path(&line[i + 2], all, get_line(line)))
      ft_all_exit(*all, "infos path isn't valid");
  }
  else
  {
    is_valid_color(all, line);
    update_color(all, &line[i + 1], line[0]);
  }
}