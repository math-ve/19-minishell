/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:13:45 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:39:51 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		error_perm(t_data *data, char *file_name)
{
	(void)data;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Permission denied", 2);
	write(2, "\n", 1);
	errno = 1;
	return (0);
}

int		error_no_such_file(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	write(2, "\n", 1);
	errno = 127;
	return (0);
}

int		error_no_such_file2(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	write(2, "\n", 1);
	errno = 1;
	return (0);
}

int		error_cmd_not_not_found(t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->tokens->content, 2);
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	errno = 127;
	return (0);
}

int		ft_errors_dispatch(t_data *data, int code, char *str)
{
	if (code == 2)
		error_cmd_not_not_found(data);
	else if (code == 3)
		errno = 1;
	else if (code == 9)
		error_no_such_file(str);
	else if (code == 10)
		error_redir();
	else if (code == 11)
		error_no_such_file2(str);
	else if (code == 12)
		error_perm(data, str);
	return (0);
}
