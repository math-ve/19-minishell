/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:53:53 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 20:33:20 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_valid_path(char *path)
{
	if (path[0] == ' ')
		return (0);
	else
		return (1);
}

int		is_symbolic_link(char *token)
{
	struct stat	infos;
	char		*perm_octal;

	lstat(token, &infos);
	perm_octal = change_to_octal(infos.st_mode);
	if (perm_octal[0] == '1' && perm_octal[1] == '2')
	{
		stat(token, &infos);
		free(perm_octal);
		perm_octal = change_to_octal(infos.st_mode);
	}
	return (0);
}

int		ft_path_2(struct stat infos, char *perm_octal, char *path)
{
	if (lstat(path, &infos) == -1)
		return (1);
	perm_octal = change_to_octal(infos.st_mode);
	if ((perm_octal[0] == '1' && perm_octal[1] == '2') ||
		ft_strncmp(perm_octal, "0", 1) == 0)
	{
		stat(path, &infos);
		free(perm_octal);
		perm_octal = change_to_octal(infos.st_mode);
		if ((perm_octal[0] == '1' && perm_octal[1] == '2') ||
			ft_strncmp(perm_octal, "0", 1) == 0)
		{
			free(perm_octal);
			return (2);
		}
	}
	free(perm_octal);
	return (3);
}

int		ft_path(t_data *data, char *path)
{
	t_list		*temp_token;
	struct stat	infos;

	temp_token = data->tokens;
	if (check_valid_path(path))
	{
		if (ft_path_2(infos, data->perm_octal, path) == 1)
			return (ft_errors_dispatch(data, 9, path));
		else if (ft_path_2(infos, data->perm_octal, path) == 2)
			return (ft_errors_dispatch(data, 9, data->tokens->content));
		stat(path, &infos);
		data->perm_octal = change_to_octal(infos.st_mode);
		data->perm_all = ft_substr(data->perm_octal,
			ft_strlen(data->perm_octal) - 3, 3);
		data->perm_owner = ft_substr(data->perm_all, 0, 1);
		if ((ft_atoi(data->perm_owner) % 2 == 0) || (ft_atoi(data->perm_owner)
			!= 5 && ft_atoi(data->perm_owner) != 7 && check_if_bin(path) == 1))
		{
			free_perm(data->perm_all, data->perm_owner, data->perm_octal);
			return (ft_errors_path(temp_token->content, path));
		}
		errno = 0;
	}
	free_perm(data->perm_all, data->perm_owner, data->perm_octal);
	return (1);
}
