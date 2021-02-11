/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-eyn <mvan-eyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:34:40 by mvan-eyn          #+#    #+#             */
/*   Updated: 2020/11/25 19:50:22 by mvan-eyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_malloc_s(char const *s, char c)
{
	int a;
	int counter;

	a = 0;
	counter = 0;
	while (s[a] != '\0')
	{
		while (s[a] != '\0' && s[a] == c)
			a++;
		if (s[a] != '\0' && s[a] != c)
		{
			counter++;
			while (s[a] != '\0' && s[a] != c)
				a++;
		}
	}
	return (counter);
}

static void	ft_free(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*ft_write(char const *s, char c, char **tab)
{
	size_t			i;
	unsigned int	j;
	char			*dest;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
		i++;
	dest = ft_substr(s, j, i);
	if (dest == NULL)
		ft_free(tab);
	return (dest);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if (!(tab = malloc((ft_malloc_s(s, c) + 2) * sizeof(char*))))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[j++] = ft_write(&s[i], c, tab);
			while (s[i] != c && s[i])
				i++;
		}
	}
	tab[j] = (NULL);
	return (tab);
}
