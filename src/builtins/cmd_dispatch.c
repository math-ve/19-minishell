/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:55:06 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:41:56 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		cmd_dispatch(t_data *data)
{
	if (data->tokens)
	{
		if (ft_strncmp(data->tokens->content, "echo", 5) == 0)
			return (ft_echo(data));
		if (ft_strncmp(data->tokens->content, "cd", 3) == 0)
			return (ft_cd(data));
		if (ft_strncmp(data->tokens->content, "pwd", 5) == 0)
			return (ft_pwd(data));
		if (ft_strncmp(data->tokens->content, "env", 4) == 0)
			return (ft_env(data));
		if (ft_strncmp(data->tokens->content, "export", 7) == 0)
			return (ft_export(data));
		if (ft_strncmp(data->tokens->content, "unset", 6) == 0)
			return (ft_unset(data));
		if (ft_strncmp(data->tokens->content, "exit", 5) == 0)
			return (ft_exit(data));
		else
			return (ft_bin(data));
	}
	else
		return (0);
}
