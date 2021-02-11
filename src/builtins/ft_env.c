/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:05:07 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:52:23 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*print_underscore(t_data *data)
{
	t_list	*temp_env;
	char	*new_underscore;
	char	*str_to_print;

	str_to_print = ft_strdup("");
	new_underscore = NULL;
	temp_env = data->full_env;
	while (temp_env)
	{
		if (ft_strncmp(temp_env->content, "PATH=", 4) == 0)
			new_underscore = ft_substr(temp_env->content, 5,
				ft_strlen(temp_env->content) - 5);
		temp_env = temp_env->next;
	}
	if (new_underscore)
	{
		new_underscore = ft_strjoin_free_all(ft_strdup("_="), new_underscore);
		new_underscore = ft_strjoin_free_all(new_underscore, ft_strdup("/env"));
		str_to_print = ft_strjoin_free_all(str_to_print, new_underscore);
		str_to_print = add_char(str_to_print, '\n');
	}
	return (str_to_print);
}

int		ft_env(t_data *data)
{
	t_list	*temp;
	char	*str_to_print;

	if (data->was_pipe)
		dup2(data->stdout_cpy, 1);
	str_to_print = ft_strdup("");
	temp = data->full_env;
	while (temp)
	{
		if (ft_strncmp(temp->content, "_=", 2) != 0)
		{
			str_to_print = ft_strjoin_free(str_to_print, temp->content);
			str_to_print = add_char(str_to_print, '\n');
		}
		temp = temp->next;
	}
	str_to_print = ft_strjoin_free_all(str_to_print, print_underscore(data));
	if (!data->is_pipe)
		ft_putstr_fd(str_to_print, 1);
	else
		ft_pipe(data, str_to_print);
	free(str_to_print);
	return (0);
}
