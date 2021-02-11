/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:13:45 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:36:06 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_errors_export(char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	errno = 127;
	return (0);
}

int		ft_error_export(char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	write(2, "\n", 1);
	errno = 1;
	return (0);
}

int		ft_errors(t_data *data, int code)
{
	ft_putstr_fd("minishell: ", 2);
	if (code == 127)
	{
		ft_putstr_fd(data->tokens->content, 2);
		ft_putstr_fd(": command not found", 2);
	}
	else if (code == 1)
		ft_putstr_fd("export: `", 2);
	else if (code == 100)
	{
		ft_putstr_fd(data->tokens->content, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	write(2, "\n", 1);
	errno = 127;
	return (0);
}

int		ft_error_exit(t_data *data, int status)
{
	t_list	*temp_token;

	temp_token = data->tokens->next;
	ft_putstr_fd("minishell: exit: ", 2);
	if (status == 2)
	{
		ft_putstr_fd(temp_token->content, 2);
		ft_putstr_fd(": numeric argument required", 2);
	}
	else if (status == 1)
		ft_putstr_fd("too many arguments", 2);
	write(2, "\n", 1);
	errno = status;
	free_list(data);
	free_env(data);
	exit(errno);
	return (0);
}

int		ft_errors_line2(char *line)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(line, 2);
	write(2, "'", 1);
	write(2, "\n", 1);
	errno = 1;
	return (0);
}
