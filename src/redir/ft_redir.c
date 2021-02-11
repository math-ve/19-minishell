/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:10:18 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:54:06 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		redir_input(t_data *data)
{
	t_list		*temp_token;
	t_list		*token_file_name;
	struct stat	infos;

	temp_token = data->tokens;
	data->is_input = 1;
	while (temp_token)
	{
		if (ft_strncmp(temp_token->content, "<", 1) == 0)
		{
			token_file_name = temp_token->next;
			if (lstat(token_file_name->content, &infos) == 0)
			{
				delete_redir_tokens(data, "<");
				if (check_perm(infos) == 0)
					return (ft_error_delete(data, 12, token_file_name));
				return (ft_fd_create(token_file_name, data));
			}
			delete_redir_tokens(data, "<");
			return (ft_error_delete(data, 11, token_file_name));
		}
		temp_token = temp_token->next;
	}
	return (0);
}

int		redir_append(t_data *data)
{
	t_list	*temp_token;
	t_list	*token_file_name;
	int		fd;

	temp_token = data->tokens;
	while (temp_token)
	{
		if (ft_strncmp(temp_token->content, ">>", 2) == 0)
		{
			token_file_name = temp_token->next;
			fd = open(token_file_name->content, O_RDWR |
				O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
			delete_redir_tokens(data, ">>");
			delete_redir_tokens(data, token_file_name->content);
			return (fd);
		}
		temp_token = temp_token->next;
	}
	return (0);
}

int		redir_write(t_data *data)
{
	t_list	*temp_token;
	t_list	*token_file_name;
	int		fd;

	temp_token = data->tokens;
	while (temp_token)
	{
		if (ft_strncmp(temp_token->content, ">", 1) == 0)
		{
			token_file_name = temp_token->next;
			fd = open(token_file_name->content, O_RDWR
				| O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			delete_redir_tokens(data, ">");
			delete_redir_tokens(data, token_file_name->content);
			return (fd);
		}
		temp_token = temp_token->next;
	}
	return (0);
}

int		ft_is_redir(t_list *temp_token)
{
	if ((ft_strncmp(temp_token->content, ">", 1) == 0) ||
			(ft_strncmp(temp_token->content, ">>", 2) == 0) ||
			(ft_strncmp(temp_token->content, "<", 1) == 0))
		return (1);
	return (0);
}

int		ft_redir(t_data *data)
{
	t_list	*temp_token;
	int		fd;

	temp_token = data->tokens;
	while (temp_token && data->tokens)
	{
		if (ft_is_redir(temp_token))
		{
			data->is_input = 0;
			if (!temp_token->next)
				return (ft_delete_and_free(data, temp_token));
			if (dispatch_redir(temp_token->content) == 1)
				fd = redir_write(data);
			else if (dispatch_redir(temp_token->content) == 2)
				fd = redir_append(data);
			else if (dispatch_redir(temp_token->content) == 3)
				fd = redir_input(data);
			if (data->tokens)
				temp_token = data->tokens;
		}
		temp_token = temp_token->next;
	}
	ft_manage_dup(fd, data);
	return (0);
}
