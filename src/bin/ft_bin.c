/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:51:30 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 20:18:11 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_directory_2(char *token, t_data *data, struct stat infos)
{
	stat(token, &infos);
	free(data->perm_octal);
	data->perm_octal = change_to_octal(infos.st_mode);
	if (data->perm_octal[0] == '4')
	{
		free(data->perm_octal);
		return (1);
	}
	else if (data->perm_octal[0] == '1' && data->perm_octal[1] == '2')
	{
		free(data->perm_octal);
		return (2);
	}
	return (3);
}

int		is_directory(t_data *data, char *token)
{
	struct stat	infos;

	if (lstat(token, &infos) == -1)
		return (0);
	data->perm_octal = change_to_octal(infos.st_mode);
	if ((token[0] == '.' && token[1] == '/') ||
		(ft_strlen(token) > 0 && token[ft_strlen(token) - 1] == '/'))
	{
		if (data->perm_octal[0] == '1' && data->perm_octal[1] == '2')
		{
			if (is_directory_2(token, data, infos) == 1)
				return (1);
			else if (is_directory_2(token, data, infos) == 2)
				return (2);
		}
		if (data->perm_octal && data->perm_octal[0] == '4')
		{
			free(data->perm_octal);
			return (1);
		}
	}
	free(data->perm_octal);
	return (0);
}

int		ft_bin_3(t_data *data, t_list *temp_token, struct stat infos)
{
	data->env_array = fill_array_env(data);
	data->token_array = fill_token_array(temp_token);
	data->bin_array = path_sub_bin(data, temp_token->content);
	if ((!data->bin_array || !data->bin_array[0])
		&& lstat(temp_token->content, &infos) != 0
		&& data->is_no_path == 0)
	{
		free_bin(data->bin_array, data->token_array, data->env_array);
		return (ft_errors_dispatch(data, 9, data->tokens->content));
	}
	else if ((!data->bin_array ||
		!data->bin_array[0]) && lstat(temp_token->content, &infos) == 0)
	{
		free_bin(data->bin_array, data->token_array, data->env_array);
		return (ft_execve(data, temp_token->content, data->token_array,
			data->env_array));
	}
	return (1);
}

int		ft_bin2(t_data *data, t_list *temp_token, char *temp, struct stat infos)
{
	int i;

	i = 0;
	while (data->bin_array && data->bin_array[i])
	{
		temp = fill_temp(data, temp_token, temp, i);
		if (lstat(temp, &infos) == 0)
		{
			if (check_slash_path(temp_token->content))
			{
				free(temp);
				free_bin(data->bin_array, data->token_array,
					data->env_array);
				return (ft_errors_dispatch(data, 9, data->tokens->content));
			}
			if (ft_path(data, temp) == 1)
				ft_execve(data, temp, data->token_array, data->env_array);
			free_bin(data->bin_array, data->token_array, data->env_array);
			free_norme(data, temp);
			return (0);
		}
		i++;
	}
	free(temp);
	return (1);
}

int		ft_bin(t_data *data)
{
	t_list		*temp_token;
	struct stat	infos;
	char		*temp;

	temp = NULL;
	temp_token = data->tokens;
	if (ft_bin_3(data, temp_token, infos) == 0)
		return (0);
	if (is_directory(data, temp_token->content) == 1)
	{
		free_bin(data->bin_array, data->token_array, data->env_array);
		return (ft_errors_directory(temp_token->content));
	}
	if (check_if_bin(temp_token->content) ||
		(lstat(temp_token->content, &infos) == 0 && data->is_colon))
	{
		if (ft_path(data, temp_token->content))
			ft_execve(data, temp_token->content, data->token_array,
				data->env_array);
	}
	else if (ft_bin2(data, temp_token, temp, infos) == 0)
		return (0);
	bin_end(data, temp);
	return (0);
}
