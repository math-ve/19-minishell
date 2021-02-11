/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:10:18 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:39:56 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_signal(int sig_code, void *ptr)
{
	static t_data *data = NULL;

	if (sig_code == 2 && data != NULL)
	{
		kill(0, 0);
		write(1, "\n", 1);
		if (data->pid1 == 0)
		{
			free(data->line);
			ft_putstr_fd("minishell >", 1);
		}
		data->pid1 = 0;
		errno = 130;
		data->line = NULL;
	}
	if (data == NULL)
		data = ptr;
}

void	ft_signal_2(int sig_code, void *ptr)
{
	static t_data	*data = NULL;
	char			*pid_char;

	(void)sig_code;
	if (data != NULL && data->pid1 > 0)
	{
		kill(0, 0);
		pid_char = ft_itoa(data->pid1);
		write(2, "[1]    ", 8);
		write(2, pid_char, ft_strlen(pid_char));
		write(2, " quit (core dumped)\n", 20);
		free(pid_char);
	}
	else if (data != NULL)
		ft_putstr_fd("\nminishell >", 1);
	if (data == NULL)
		data = ptr;
}
