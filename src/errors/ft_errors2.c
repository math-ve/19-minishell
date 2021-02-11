/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:13:45 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:35:10 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_errors_cd(t_data *data, int code)
{
	t_list	*temp_token;

	temp_token = data->tokens->next;
	ft_putstr_fd("minishell: cd: ", 2);
	if (code == 1)
	{
		errno = 1;
		ft_putstr_fd("HOME not set", 2);
	}
	else if (code == 2)
	{
		errno = 1;
		ft_putstr_fd("too many arguments", 2);
	}
	else if (code == 3)
	{
		ft_putstr_fd(temp_token->content, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	write(2, "\n", 1);
	return (0);
}

int		ft_errors_unset(char *token)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	write(1, "\n", 1);
	errno = 1;
	return (0);
}

int		ft_errors_path(char *token, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	if (ft_strncmp(token, "cd", 3) != 0)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd(token, 2);
		write(2, ": ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied", 2);
	}
	write(2, "\n", 1);
	errno = 126;
	return (0);
}

int		ft_errors_directory(char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(": Is a directory", 2);
	write(2, "\n", 1);
	errno = 126;
	return (0);
}

int		ft_errors_line(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, &c, 1);
	write(2, "'", 1);
	write(2, "\n", 1);
	errno = 1;
	return (0);
}
