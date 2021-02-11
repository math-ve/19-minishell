/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:43:59 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 15:00:05 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		should_we_remove(char *token, int pos)
{
	if (token[pos] == '\\' && token[pos + 1] != '\\')
		return (1);
	return (0);
}

char	*handle_backslash(char *token)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = strdup("");
	if (ft_strlen(token) > 0 && ft_strncmp(token, "\\", ft_strlen(token)) == 0)
	{
		new_str = add_char(new_str, '\\');
		free(token);
		return (new_str);
	}
	while (token[i])
	{
		if ((token[i] == '\\' && token[i + 1] != '\\') ||
			(token[i] == '\\' && token[i + 1] != ' ') ||
			(token[i] == '\\' && is_before(token, i, '\\')
				&& token[i + 1] == '\\'))
			i++;
		if (token[i])
			new_str = add_char(new_str, token[i++]);
	}
	free(token);
	return (new_str);
}
