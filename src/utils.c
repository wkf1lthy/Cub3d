#include "../includes/cub3d.h"

void ft_all_exit(t_all *all, char *str)
{
    free_all(all);
    if(str)
         exit_error(str);
}

void free_tab(char **tab)
{
	int i;

	i = 0;
	if(!tab)
		return ;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int only_spaces(char *str)
{
	int i = 0;
  	while(str[i] && str[i] != '\n')
	{
		if(!ft_isspace((unsigned char)str[i]))
			return(1);
       	i++;
	}
	return(0);

}

void free_all(t_all *all)
{
  int i;

  i = 0;
  if(all->map)
    free_tab(all->map);
  if(all->infos)
    free(all->infos);
  while(i < NB_TEXT)
  {
    if(all->tab_textures[i])
      mlx_delete_texture(all->tab_textures[i]);
    i++;
  }
  if(all->mlx)
    mlx_terminate(all->mlx);
  free(all);
}

void exit_error(char *str)
{
    printf("Error\n%s\n", str);
    exit(EXIT_FAILURE);
}

char	*ft_strstr(const char *str1, const char *str2)
{
	size_t	i;
	size_t	j;

	if (!*str2)
		return ((char *)str1);
	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == str2[0])
		{
			j = 0;
			while (str2[j] != '\0')
			{
				if (str1[i + j] != str2[j])
					break ;
				j++;
			}
			if (str2[j] == '\0')
				return ((char *)&str1[i]);
		}
		i++;
	}
	return (NULL);
}