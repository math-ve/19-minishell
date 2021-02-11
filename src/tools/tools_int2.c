/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:07:42 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:20:12 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_free_int(char *parsed_nbr, int i)
{
	free(parsed_nbr);
	return (i);
}

int		ft_is_neg(int is_neg, char *nbr)
{
	is_neg = 0;
	if (nbr[0] == '-')
		is_neg = 1;
	return (is_neg);
}

int		check_int_valid(char *nbr)
{
	size_t	i;
	int		is_neg;
	char	*parsed_nbr;

	parsed_nbr = parse_nbr(nbr);
	i = 0;
	is_neg = 0;
	is_neg = ft_is_neg(is_neg, nbr);
	while (ft_isinset(parsed_nbr[i], "0123456789"))
		i++;
	if (i > ft_strlen(MAX_LLONG))
		return (ft_free_int(parsed_nbr, 1));
	else if (i < ft_strlen(MAX_LLONG))
		return (ft_free_int(parsed_nbr, 0));
	else if (i == ft_strlen(MAX_LLONG))
	{
		i = 0;
		while (ft_isinset(parsed_nbr[i++], "0123456789"))
		{
			if ((is_neg && parsed_nbr[i] > MAX_LLONG_NEG[i])
			|| (!is_neg && parsed_nbr[i] > MAX_LLONG[i]))
				return (ft_free_int(parsed_nbr, 1));
		}
	}
	return (ft_free_int(parsed_nbr, 0));
}
