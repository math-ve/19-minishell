/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:30:01 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:59:54 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pid_2(t_data *data, int *fd)
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	ft_program(data->pipeline, data);
	exit(0);
}

void	ft_pid_1(int *fd, char *path_bin, char **token_array, char **env_array)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execve(path_bin, token_array, env_array);
}

int		ft_pipe_bin(t_data *data, char *path_bin, char **token_array,
	char **env_array)
{
	int		status;
	int		fd[2];

	status = 0;
	if (pipe(fd) == -1)
		return (0);
	data->pid1 = fork();
	if (data->pid1 < 0)
		return (0);
	if (data->pid1 == 0)
		ft_pid_1(fd, path_bin, token_array, env_array);
	data->pid2 = fork();
	if (data->pid2 < 0)
		return (0);
	if (data->pid2 == 0)
		ft_pid_2(data, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(data->pid2, &status, 0);
	dup2(data->stdin_cpy, 0);
	return (status);
}

void	ft_pipe2(int *fd, t_data *data)
{
	dup2(fd[0], 0);
	if (is_empty_str(data->pipeline))
		errno = 1;
	ft_program(data->pipeline, data);
	dup2(data->stdin_cpy, 0);
}

int		ft_pipe(t_data *data, char *str)
{
	int	fd[2];
	int	status;

	status = 0;
	if (pipe(fd) == -1)
		return (0);
	data->pid1 = fork();
	if (data->pid1 < 0)
		return (0);
	if (data->pid1 == 0)
	{
		close(fd[0]);
		if (data->is_redir)
			ft_putstr_fd(str, 1);
		else
			ft_putstr_fd(str, fd[1]);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(-1, &status, 0);
	ft_pipe2(fd, data);
	return (status);
}
