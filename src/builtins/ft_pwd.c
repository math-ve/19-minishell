/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:22:35 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 20:03:25 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		ft_pwd(t_data *data)
{
	char	*str_to_print;
	char	*path;

	if (data->was_pipe)
		dup2(data->stdout_cpy, 1);
	str_to_print = get_value_env(data, "PWD");
	if (!str_to_print || str_to_print[0] != '/')
	{
		path = getcwd(NULL, 0);
		free(str_to_print);
		str_to_print = ft_strdup("");
		str_to_print = ft_strjoin_free_all(str_to_print, path);
	}
	str_to_print = add_char(str_to_print, '\n');
	if (!data->is_pipe)
		ft_putstr_fd(str_to_print, 1);
	else
		ft_pipe(data, str_to_print);
	free(str_to_print);
	return (0);
}
