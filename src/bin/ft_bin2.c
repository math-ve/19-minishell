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

char	*is_no_path(char **path_array)
{
	free_array(path_array);
	if (!(path_array = malloc(sizeof(char *) * 2)))
		return (NULL);
	path_array[0] = ft_strdup("/");
	path_array[1] = NULL;
	return (NULL);
}

void	set_errno(int status)
{
	if (status == 0)
		errno = 0;
	else if (status == 256)
		errno = 1;
	else if (status == 2048)
		errno = 0;
	else if (status == 512)
		errno = 2;
	else if (status == 32512)
		errno = 127;
}

int		check_if_bin(char *token)
{
	if (token[0] == '/' || (token[0] == '.' && token[1] == '/'))
		return (1);
	else
		return (0);
}

int		check_slash_path(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*fill_temp(t_data *data, t_list *temp_token, char *temp, int i)
{
	if (ft_strncmp(temp_token->content, data->bin_array[i],
		ft_strlen(data->bin_array[i])) != 0)
	{
		free(temp);
		temp = ft_strjoin(data->bin_array[i], temp_token->content);
	}
	return (temp);
}
