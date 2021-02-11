/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:13:20 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:50:43 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			is_not_dollar(char *token, int i)
{
	if ((token[i] && token[i] != '$') ||
		(token[i] && token[i] == '$' && is_before(token, i, '\\')) ||
		(token[i] && token[i] == '$' && !ft_check_surround(token, i)) ||
		(token[i] == '$' && ft_isalnum(token[i + 1]) == 0))
		return (1);
	else
		return (0);
}

char		*return_status(char *token, char *new_str)
{
	free(token);
	free(new_str);
	return (ft_itoa(errno));
}

char		*get_env(t_list *temp_env, char *token, int i, char *parsed_var)
{
	char	*env_after_egal;

	env_after_egal = ft_substr(temp_env->content,
		ft_strlen(parsed_var), ft_strlen(temp_env->content)
		- ft_strlen(parsed_var));
	env_after_egal = check_space_dq(env_after_egal, token,
		i - ft_strlen(parsed_var), i);
	env_after_egal = check_backslash(env_after_egal);
	return (env_after_egal);
}

int			is_dollar(t_data *data, char *token, int *i)
{
	t_list *temp_env;

	temp_env = data->full_env;
	if (token[(*i) + 1] == '?')
		return (1);
	data->has_been_trad = 1;
	data->parsed_var = ft_parse_token(token, i);
	while (temp_env)
	{
		if ((ft_strncmp(temp_env->content, data->parsed_var,
			ft_strlen(data->parsed_var)) == 0))
		{
			data->env_after_egal = get_env(temp_env, token, (*i),
				data->parsed_var);
			data->new_str = ft_strjoin_free_all(data->new_str,
				data->env_after_egal);
			break ;
		}
		temp_env = temp_env->next;
	}
	free(data->parsed_var);
	return (3);
}

char		*handle_dollar(t_data *data, char *token)
{
	int		i;

	i = 0;
	data->new_str = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '$' && ft_check_surround(token, i)
			&& is_before(token, i, '\\') == 0 && (ft_isalnum(token[i + 1])
			|| token[i + 1] == '?' || token[i + 1] == '_'))
		{
			if (is_dollar(data, token, &i) == 1)
				return (return_status(token, data->new_str));
		}
		if (is_not_dollar(token, i))
			data->new_str = add_char(data->new_str, token[i++]);
	}
	free(token);
	return (data->new_str);
}
