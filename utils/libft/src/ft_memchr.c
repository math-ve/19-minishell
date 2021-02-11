/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-eyn <mvan-eyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:28:21 by mvan-eyn          #+#    #+#             */
/*   Updated: 2020/11/25 19:50:28 by mvan-eyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*source;

	source = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (source[i] == (unsigned char)c)
			return (&source[i]);
		i++;
	}
	return (NULL);
}
