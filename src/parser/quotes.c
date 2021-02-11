/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:48:01 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:23:23 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*add_sq(char *str, char *line, int *i)
{
	char	*new_str;
	int		not_closed;

	not_closed = 1;
	new_str = add_char(str, line[(*i)]);
	(*i)++;
	while (line[(*i)] && not_closed)
	{
		if (line[(*i)] == '\'')
		{
			new_str = add_char(new_str, line[(*i)]);
			return (new_str);
		}
		else
		{
			if (line[(*i)] == '\"' || line[(*i)] == '\\')
				new_str = add_char(new_str, '\\');
			new_str = add_char(new_str, line[(*i)]);
			(*i)++;
		}
	}
	if (not_closed)
		return (ft_error_eof('\'', new_str));
	(*i)--;
	return (NULL);
}

int		is_valid_close(char *line, int *i)
{
	if ((line[(*i)] == '\"' && line[(*i) - 1] != '\\') ||
			(line[(*i)] == '\"' && line[(*i) - 1] == '\\' &&
			line[(*i) - 2] == '\\'))
		return (1);
	else
		return (0);
}

char	*add_dq(char *str, char *line, int *i)
{
	char	*new_str;
	int		not_closed;

	not_closed = 1;
	new_str = add_char(str, line[(*i)]);
	(*i)++;
	while (line[(*i)] && not_closed)
	{
		if (is_valid_close(line, i))
			return (add_char(new_str, line[(*i)]));
		else
		{
			if (line[(*i)] == '\'' ||
				((line[(*i)] == '\\' && line[(*i) + 1] != '\"')
				&& line[(*i) + 1] != '$' && (line[(*i)] == '\\' &&
				line[(*i) + 1] != '\\')))
				new_str = add_char(new_str, '\\');
			new_str = add_char(new_str, line[(*i)]);
			(*i)++;
		}
	}
	if (not_closed)
		return (ft_error_eof('\"', new_str));
	(*i)--;
	return (NULL);
}
