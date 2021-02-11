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

int		print_declare(t_data *data)
{
	t_list	*temp_env;
	int		i;
	char	*str_to_print;

	temp_env = data->full_env;
	str_to_print = ft_strdup("");
	while (temp_env)
	{
		i = 0;
		if (((char *)temp_env->content)[0] == '_')
			break ;
		str_to_print = get_str_to_print(temp_env, str_to_print, &i);
		temp_env = temp_env->next;
	}
	if (data->is_pipe)
		ft_pipe(data, str_to_print);
	else
		ft_putstr_fd(str_to_print, 1);
	free(str_to_print);
	return (0);
}

int		check_egal(char *token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	if (token[i] == '=')
		return (1);
	return (0);
}

char	*get_var_name(char *token)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = ft_strdup("");
	while (token && token[i] && token[i] != '=')
	{
		var_name = add_char(var_name, token[i]);
		i++;
	}
	return (var_name);
}

void	ft_export_2(t_data *data, t_list *temp_token)
{
	char	*temp;

	temp = get_var_name(temp_token->content);
	save_underscore(data, temp);
	if (check_entry(data, temp_token->content))
	{
	}
	else
		ft_lstadd_back(&data->full_env,
			ft_lstnew(ft_strdup(temp_token->content)));
	free(temp);
}

int		ft_export(t_data *data)
{
	t_list	*temp_token;

	if (data->was_pipe)
		dup2(data->stdout_cpy, 1);
	if (!data->tokens->next)
		return (print_declare(data));
	if (data->is_pipe)
		return (ft_pipe(data, NULL));
	if (data->was_pipe)
		return (0);
	temp_token = data->tokens->next;
	while (temp_token)
	{
		if (check_if_valid(temp_token->content))
			ft_export_2(data, temp_token);
		temp_token = temp_token->next;
	}
	return (0);
}
