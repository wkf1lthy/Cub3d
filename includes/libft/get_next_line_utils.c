/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 22:29:58 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/19 18:43:19 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_buf_cut(char *buffer)
{
	int	i;
	int	j;
	int	indice;

	j = 0;
	i = 0;
	indice = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[j])
		j++;
	while (indice < j - i)
	{
		buffer[indice] = buffer[indice + i];
		indice++;
	}
	buffer[indice] = '\0';
}

int	ft_len(char *s, int j)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	if (j == 1)
		c = '\n';
	while (s && s[i] && s[i] != c)
		i++;
	if (c == '\n' && s && s[i] && s[i] == '\n')
		i++;
	return (i);
}

char	*test(char *s1, char *dest)
{
	free(s1);
	if (dest)
	{
		if (dest[0] == '\0')
		{
			free(dest);
			dest = NULL;
		}
	}
	return (dest);
}

char	*ft_join(char *s1, char *s2)
{
	char	*dest;
	int		t;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * ((ft_len(s1, 1) + ft_len(s2, 0)) + 1));
	if (dest)
	{
		while (s1 && s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
		t = 0;
		while (s2 && s2[t] && s2[t] != '\n')
		{
			dest[i + t] = s2[t];
			t++;
		}
		dest[i + t] = '\n';
		if (s2 && s2[t] && s2[t] == '\n')
			t++;
		dest[i + t] = '\0';
	}
	return (test(s1, dest));
}
