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

int		check_perm(struct stat infos)
{
	char	*perm_octal;
	int		index;

	perm_octal = change_to_octal(infos.st_mode);
	index = ft_strlen(perm_octal) - 3;
	if (perm_octal[index] == '0')
	{
		free(perm_octal);
		return (0);
	}
	free(perm_octal);
	return (1);
}

int		ft_error_delete(t_data *data, int i, t_list *token_file_name)
{
	ft_errors_dispatch(data, i, token_file_name->content);
	delete_redir_tokens(data, token_file_name->content);
	return (0);
}

int		ft_fd_create(t_list *token_file_name, t_data *data)
{
	int fd;

	fd = open(token_file_name->content, O_RDWR);
	delete_redir_tokens(data, token_file_name->content);
	return (fd);
}

void	ft_manage_dup(int fd, t_data *data)
{
	if (fd == 0)
		free_list(data);
	if (data->is_input && fd != 0)
		dup2(fd, 0);
	else
		dup2(fd, 1);
}

int		ft_delete_and_free(t_data *data, t_list *temp_token)
{
	delete_redir_tokens(data, temp_token->content);
	free_list(data);
	return (ft_errors_dispatch(data, 10, NULL));
}
