/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:02:07 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:37:33 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_set_shlvl2(int lvl, t_data *data)
{
	char	*temp;
	char	*shlvl;

	if ((lvl == 2147483647 || lvl < 0))
		lvl = -1;
	else if (lvl >= 2000000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(lvl + 1, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		lvl = 0;
	}
	temp = ft_itoa(lvl + 1);
	shlvl = ft_strjoin("SHLVL=", temp);
	if (check_entry(data, shlvl))
	{
	}
	else
		ft_lstadd_back(&data->full_env, ft_lstnew(ft_strdup(shlvl)));
	free(temp);
	free(shlvl);
}

void		ft_set_shlvl(t_data *data)
{
	t_list	*temp_env;
	char	*shlvl;
	int		lvl;
	char	*env_line;

	temp_env = data->full_env;
	env_line = NULL;
	shlvl = NULL;
	while (temp_env)
	{
		if (ft_strncmp(temp_env->content, "SHLVL=", 5) == 0)
			env_line = ft_strdup(temp_env->content);
		temp_env = temp_env->next;
	}
	lvl = 0;
	if (env_line)
		shlvl = get_env_after_egal(env_line);
	if (shlvl)
		lvl = ft_atoi(shlvl);
	if (shlvl && !is_numeric(shlvl))
		lvl = 0;
	free(shlvl);
	ft_set_shlvl2(lvl, data);
	free(env_line);
}

void		save_pwd(t_data *data)
{
	char	*new_pwd;
	char	*new_path;

	new_path = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", new_path);
	if (check_entry(data, new_pwd) == 0)
		ft_lstadd_back(&data->full_env, ft_lstnew(ft_strdup(new_pwd)));
	free(new_path);
	free(new_pwd);
}

void		save_underscore(t_data *data, char *token)
{
	char	*new_unserscore;

	new_unserscore = ft_strjoin("_=", token);
	if (check_entry(data, new_unserscore))
	{
	}
	else
		ft_lstadd_back(&data->full_env, ft_lstnew(ft_strdup(new_unserscore)));
	free(new_unserscore);
}

void		save_env_lst(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&data->full_env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	save_pwd(data);
	ft_set_shlvl(data);
	save_underscore(data, "/bin/bash");
}
