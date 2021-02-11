/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:26:40 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:24:51 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_list(t_data *data)
{
	t_list	*tmp;

	while (data->tokens)
	{
		free(data->tokens->content);
		tmp = data->tokens;
		data->tokens = data->tokens->next;
		free(tmp);
	}
	data->tokens = NULL;
}

void	free_env(t_data *data)
{
	t_list	*tmp;

	while (data->full_env)
	{
		free(data->full_env->content);
		tmp = data->full_env;
		data->full_env = data->full_env->next;
		free(tmp);
	}
	data->full_env = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char	*free_return_null(char *line)
{
	free(line);
	return (NULL);
}

void	free_perm(char *perm_all, char *perm_owner, char *perm_octal)
{
	free(perm_all);
	free(perm_octal);
	free(perm_owner);
}
