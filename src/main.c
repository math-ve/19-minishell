/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:33:37 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 14:39:00 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*ft_program(char *line, t_data *data)
{
	while (line)
	{
		if (data->is_pipe)
			data->was_pipe = 1;
		data->is_redir = 0;
		data->is_pipe = 0;
		free_list(data);
		line = ft_parser(line, data);
		ft_traduction(data);
		if (data->is_redir)
			ft_redir(data);
		cmd_dispatch(data);
		if (data->is_redir || data->was_pipe)
		{
			dup2(data->stdin_cpy, 0);
			dup2(data->stdout_cpy, 1);
			data->is_redir = 0;
		}
		data->is_pipe = 0;
		if (data->was_pipe)
			free(data->pipeline);
		data->was_pipe = 0;
		data->pid1 = 0;
	}
	return (line);
}

static int	ft_prompt(t_data *data)
{
	while (1)
	{
		write(1, "minishell >", 11);
		if (!get_next_line(0, &data->line))
		{
			write(1, "exit\n", 5);
			return (errno);
		}
		ft_program(data->line, data);
	}
}

void		ft_init(t_data *data)
{
	data->full_env = NULL;
	data->tokens = NULL;
	data->pipeline = NULL;
	data->redir_line = NULL;
	data->line = NULL;
	data->perm_octal = NULL;
	data->perm_all = NULL;
	data->perm_owner = NULL;
	data->token = NULL;
	data->parsed_var = NULL;
	data->env_after_egal = NULL;
	data->new_str = NULL;
	data->is_pipe = 0;
	data->is_redir = 0;
	data->was_pipe = 0;
	data->has_been_trad = 0;
	data->is_colon = 0;
	data->stdin_cpy = dup(0);
	data->stdout_cpy = dup(1);
	data->pid1 = 0;
	data->pid2 = 0;
	data->is_no_path = 0;
	data->token_array = NULL;
	data->env_array = NULL;
	data->bin_array = NULL;
}

int			main(int argc, char **argv, char **envp)
{
	t_data data;

	signal(2, (void (*)(int))ft_signal);
	ft_signal(2, &data);
	signal(3, (void (*)(int))ft_signal_2);
	signal(15, (void (*)(int))ft_signal);
	ft_signal_2(3, &data);
	ft_init(&data);
	data.is_input = 0;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 1))
	{
		save_env_lst(&data, envp);
		ft_test(&data, ft_strdup(argv[2]));
	}
	else
	{
		save_env_lst(&data, envp);
		ft_prompt(&data);
	}
	free_list(&data);
	free_env(&data);
	free(data.pipeline);
	return (errno);
}
