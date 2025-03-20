/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:59:21 by hbouchel          #+#    #+#             */
/*   Updated: 2025/03/20 19:04:31 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
