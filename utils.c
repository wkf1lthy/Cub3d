#include "../../includes/cub3d"

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
	for(int i = 0; str[i] && str[i] != '\n'; i++)
	{
		if(!isspace((unsigned char)str[i]))
			return(1);
	}
	return(0);

}
void exit_error(char *str)
{
    printf("Error\n%s\n", str);
    exit(EXIT_FAILURE);
}
