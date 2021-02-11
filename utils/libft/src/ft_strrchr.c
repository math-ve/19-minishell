/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-eyn <mvan-eyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:11:42 by mvan-eyn          #+#    #+#             */
/*   Updated: 2020/11/25 19:50:14 by mvan-eyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*last;
	int		i;

	str = (char *)s;
	last = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			last = &str[i];
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (last);
}
