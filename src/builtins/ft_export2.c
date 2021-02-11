/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 16:58:43 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 20:02:17 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_if_valid(char *token)
{
	int	i;

	i = 0;
	if (ft_isdigit(token[i]) == 1)
		return (ft_error_export(token));
	if (ft_strncmp(token, "", 1) == 0)
		return (ft_error_export(token));
	while (token[i])
	{
		if ((!(ft_isalnum(token[i])) && token[i] != '_'))
		{
			if (token[i] == '+' && token[i + 1] == '=')
				return (1);
			else if (token[i] == '=' && i == 0)
				return (ft_error_export(token));
			else if (token[i] == '=' && i != 0)
				return (1);
			else
				return (ft_error_export(token));
		}
		i++;
	}
	return (0);
}

char	*get_str_to_print(t_list *temp_env, char *str_to_print, int *i)
{
	str_to_print = ft_strjoin_free(str_to_print, "declare -x ");
	while (((char *)temp_env->content)[(*i)] != '=')
	{
		str_to_print = add_char(str_to_print,
			((char *)temp_env->content)[(*i)]);
		(*i)++;
	}
	str_to_print = add_char(str_to_print, '=');
	str_to_print = add_char(str_to_print, '\"');
	(*i)++;
	while (((char *)temp_env->content)[(*i)] != '\0')
	{
		if (((char *)temp_env->content)[(*i)] == '\\' ||
			((char *)temp_env->content)[(*i)] == '\"' ||
			((char *)temp_env->content)[(*i)] == '$')
			str_to_print = add_char(str_to_print, '\\');
		str_to_print = add_char(str_to_print,
			((char *)temp_env->content)[(*i)]);
		(*i)++;
	}
	str_to_print = add_char(str_to_print, '\"');
	str_to_print = add_char(str_to_print, '\n');
	return (str_to_print);
}
