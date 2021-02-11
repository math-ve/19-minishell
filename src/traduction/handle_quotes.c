/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:01:11 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 15:15:34 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*handle_quotes(char *token)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = strdup("");
	while (token[i])
	{
		while ((token[i] == '\'' && is_before(token, i, '\\') == 0) ||
			(token[i] == '\"' && is_before(token, i, '\\') == 0) ||
			(token[i] == '\"' && i == (int)ft_strlen(token) - 1) ||
			(token[i] == '\'' && i == (int)ft_strlen(token) - 1 &&
				is_before(token, i, '\\') == 0) ||
			(token[i] == '\'' && is_before(token, i, '\\') &&
				is_before(token, i - 1, '\\') &&
				is_before(token, i - 2, '\\') == 0))
			i++;
		if (token[i])
		{
			new_str = add_char(new_str, token[i]);
			i++;
		}
	}
	free(token);
	return (new_str);
}
