/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-eyn <mvan-eyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:34:40 by mvan-eyn          #+#    #+#             */
/*   Updated: 2020/11/25 19:50:16 by mvan-eyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		counter;
	char	*str;

	counter = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[counter])
		++counter;
	if (!(str = (char*)malloc(counter + 1 * sizeof(char))))
		return (NULL);
	counter = 0;
	while (s[counter])
	{
		str[counter] = f(counter, s[counter]);
		++counter;
	}
	str[counter] = '\0';
	return (str);
}
