/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:32:26 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 14:43:35 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_sq_right(char *token, int pos)
{
	int count;

	count = 0;
	while (token[pos])
	{
		if (token[pos] == '\'')
			count++;
		pos++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

int		check_sq_left(char *token, int pos)
{
	int	count;

	count = 0;
	while (pos > -1)
	{
		if (token[pos] == '\'')
			count++;
		pos--;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

int		check_dq_right(char *token, int pos)
{
	int	count;

	count = 0;
	while (token[pos])
	{
		if (token[pos] == '\"')
			count++;
		pos++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

int		check_dq_left(char *token, int pos)
{
	int	count;

	count = 0;
	while (pos > -1)
	{
		if (token[pos] == '\"')
			count++;
		pos--;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}
