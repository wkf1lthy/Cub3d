/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:57:56 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/21 17:35:41 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_all_exit(t_all *all, char *str)
{
	free_all(all);
	if (str)
		exit_error(str);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isspace((unsigned char)str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_all(t_all *all)
{
	int	i;

	i = 0;
	if (all->map)
		free_tab(all->map);
	if (all->infos)
		free_tab(all->infos);
	while (i < NB_TEXT)
	{
		if (all->tab_textures[i])
			mlx_delete_texture(all->tab_textures[i]);
		i++;
	}
	if (all->mlx)
		mlx_terminate(all->mlx);
	free(all);
}

void	exit_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(EXIT_FAILURE);
}
