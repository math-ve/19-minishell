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

char	**fill_array_env(t_data *data)
{
	t_list	*temp_env;
	char	**env_array;
	int		i;

	temp_env = data->full_env;
	i = 0;
	if (!(env_array = malloc(sizeof(char *) * (ft_lstsize(temp_env) + 1))))
		return (NULL);
	while (temp_env)
	{
		env_array[i] = ft_strdup(temp_env->content);
		temp_env = temp_env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

char	**fill_token_array(t_list *token)
{
	t_list	*temp;
	char	**token_array;
	int		i;

	temp = token;
	i = 0;
	if (!(token_array = malloc(sizeof(char *) * (ft_lstsize(token) + 1))))
		return (NULL);
	while (temp)
	{
		token_array[i] = ft_strdup(temp->content);
		temp = temp->next;
		i++;
	}
	token_array[i] = NULL;
	return (token_array);
}

char	**path_sub_bin(t_data *data, char *token)
{
	char	**path_array;
	char	*path_env;
	int		i;

	i = 0;
	path_env = get_value_env(data, "PATH=");
	if (path_env && (path_env[0] == ':' ||
		(ft_strlen(path_env) > 0 && path_env[ft_strlen(path_env) - 1] == ':')))
		data->is_colon = 1;
	path_array = ft_split(path_env, ':');
	while (path_array && path_array[i] &&
		ft_strncmp(token, path_array[i], ft_strlen(token)))
	{
		path_array[i] = add_char(path_array[i], '/');
		i++;
	}
	if (path_array && path_array[0] == NULL && ft_strncmp(path_env, "", 1) != 0)
	{
		free_array(path_array);
		data->is_no_path = 1;
	}
	free(path_env);
	return (path_array);
}

int		ft_execve(t_data *data, char *path_bin, char **token_array,
	char **env_array)
{
	struct stat	infos;
	int			status;

	status = 0;
	if (data->was_pipe)
		dup2(data->stdout_cpy, 1);
	if (data->is_pipe && lstat(path_bin, &infos) == 0)
		return (ft_pipe_bin(data, path_bin, token_array, env_array));
	else
	{
		data->pid1 = fork();
		if (data->pid1 == -1)
			return (0);
		else if (data->pid1 > 0)
		{
			waitpid(data->pid1, &status, 0);
			kill(data->pid1, SIGTERM);
		}
		else if (data->pid1 == 0)
			execve(path_bin, token_array, env_array);
	}
	set_errno(status);
	return (status);
}

void	bin_end(t_data *data, char *temp)
{
	ft_errors_dispatch(data, errno, NULL);
	if (data->is_pipe)
		ft_program(data->pipeline, data);
	free(temp);
	free_bin(data->bin_array, data->token_array, data->env_array);
}
