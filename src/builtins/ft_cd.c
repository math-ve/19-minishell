/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:20:56 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:46:34 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_oldpwd_2(t_data *data, int *status, t_list *temp_env)
{
	char	*env_after_egal;
	char	*oldpwd_temp;

	*status = 1;
	env_after_egal = get_env_after_egal(temp_env->content);
	oldpwd_temp = ft_strjoin_free_all(ft_strdup("OLDPWD="),
		env_after_egal);
	if (check_entry(data, oldpwd_temp))
	{
	}
	else
		ft_lstadd_back(&data->full_env,
			ft_lstnew(ft_strdup(oldpwd_temp)));
	free(oldpwd_temp);
}

int		set_oldpwd(t_data *data)
{
	t_list	*temp_env;
	char	*oldpwd_temp;
	int		status;

	status = 0;
	temp_env = data->full_env;
	while (temp_env)
	{
		if (ft_strncmp(temp_env->content, "PWD=", 4) == 0)
			set_oldpwd_2(data, &status, temp_env);
		temp_env = temp_env->next;
	}
	if (status == 0)
	{
		oldpwd_temp = ft_strjoin("OLDPWD=", "");
		if (check_entry(data, oldpwd_temp))
		{
		}
		else
			ft_lstadd_back(&data->full_env, ft_lstnew(ft_strdup(oldpwd_temp)));
		free(oldpwd_temp);
	}
	return (0);
}

int		set_pwd(t_data *data)
{
	char	*new_pwd;

	new_pwd = NULL;
	new_pwd = ft_strjoin_free_all(ft_strdup("PWD="), getcwd(NULL, 0));
	if (!new_pwd)
		new_pwd = ft_strjoin(ft_strdup("PWD="), data->tokens->next->content);
	if (check_entry(data, new_pwd))
	{
	}
	else
		ft_lstadd_back(&data->full_env, ft_lstnew(ft_strdup(new_pwd)));
	free(new_pwd);
	return (0);
}

int		cd_alone(t_data *data)
{
	t_list	*temp_env;
	char	*env_after_egal;
	char	*pwd_temp;

	temp_env = data->full_env;
	while (temp_env)
	{
		if (ft_strncmp(temp_env->content, "HOME=", 5) == 0)
		{
			env_after_egal = get_env_after_egal(temp_env->content);
			pwd_temp = ft_strjoin("PWD", env_after_egal);
			chdir(env_after_egal);
			set_oldpwd(data);
			free(pwd_temp);
			free(env_after_egal);
			return (set_pwd(data));
		}
		temp_env = temp_env->next;
	}
	return (ft_errors_cd(data, 1));
}

int		ft_cd(t_data *data)
{
	t_list	*temp_token;

	temp_token = data->tokens->next;
	if (data->is_pipe)
	{
		if (temp_token->next)
			ft_errors_cd(data, 2);
		return (ft_pipe(data, data->pipeline));
	}
	if (temp_token == NULL)
		return (cd_alone(data));
	if (temp_token->next)
		return (ft_errors_cd(data, 2));
	if (ft_strncmp(temp_token->content, "", 1) != 0 &&
		chdir(temp_token->content) == -1)
	{
		if (ft_path(data, temp_token->content) == 0)
			return (0);
		return (ft_errors_cd(data, 3));
	}
	set_oldpwd(data);
	set_pwd(data);
	return (0);
}
