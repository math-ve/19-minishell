/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:24:11 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 20:06:28 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_delete_elem(t_data *data, char *var_name, int var_len)
{
	t_list	*temp;
	t_list	*prev;

	temp = data->full_env;
	if (temp && ft_strncmp(temp->content, var_name, var_len + 1) == 0)
	{
		data->full_env = temp->next;
		free(temp->content);
		free(temp);
		return (1);
	}
	while (temp && ft_strncmp(temp->content, var_name, var_len + 1) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	prev->next = temp->next;
	free(temp->content);
	free(temp);
	return (1);
}

int		check_unset_valid(char *token)
{
	int	i;

	i = 0;
	if (ft_strncmp(token, "", 1) == 0)
		return (0);
	while (token[i])
	{
		if (ft_isalnum(token[i]) == 0 && token[i] != '_')
			return (0);
		if (ft_isdigit(token[i]) && i == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset_2(t_data *data, t_list *temp_token, t_list *temp_env, int len)
{
	char *temp;

	while (temp_env)
	{
		temp = ft_strdup(temp_env->content);
		if ((ft_strncmp(temp_token->content, temp, len) == 0) &&
			temp[len] == '=')
			ft_delete_elem(data, temp, len);
		temp_env = temp_env->next;
		free(temp);
	}
}

int		ft_unset(t_data *data)
{
	t_list	*temp_env;
	t_list	*temp_token;
	int		len;

	if (data->is_pipe)
		return (0);
	temp_env = data->full_env;
	temp_token = data->tokens->next;
	while (temp_token)
	{
		if (check_unset_valid(temp_token->content))
		{
			len = ft_strlen(temp_token->content);
			ft_unset_2(data, temp_token, temp_env, len);
		}
		else
			ft_errors_unset(temp_token->content);
		temp_env = data->full_env;
		temp_token = temp_token->next;
	}
	return (0);
}
