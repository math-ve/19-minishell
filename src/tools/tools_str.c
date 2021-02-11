/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:22:32 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:36:28 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_after_egal(char *env_line)
{
	int		i;
	char	*new_str;

	i = 0;
	while (env_line[i] != '=')
		i++;
	new_str = ft_substr(env_line, i + 1, ft_strlen(env_line) - i - 1);
	return (new_str);
}

char	*get_value_env(t_data *data, char *var)
{
	t_list	*temp_env;

	temp_env = data->full_env;
	while (temp_env)
	{
		if (ft_strncmp(temp_env->content, var, ft_strlen(var)) == 0)
			return (get_env_after_egal(temp_env->content));
		temp_env = temp_env->next;
	}
	return (NULL);
}

char	*add_char(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*add_char_split(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}

char	*remove_last_space(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	while (str[i + 1])
	{
		new_str = add_char(new_str, str[i]);
		i++;
	}
	free(str);
	return (new_str);
}
