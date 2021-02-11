/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:07:42 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:20:12 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_numeric(char *str)
{
	int	i;

	i = 0;
	while (ft_isinset(*str, "\t\f\r "))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i] == '0')
		i++;
	if (check_int_valid(&str[i]))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (ft_isinset(str[i], "\t "))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int		check_entry(t_data *data, char *token)
{
	t_list	*temp_env;
	char	*temp_token;
	int		i;

	i = 1;
	temp_env = data->full_env;
	while (token && token[i] && token[i - 1] != '=' && token[i] != '+')
		i++;
	temp_token = ft_substr(token, 0, i);
	while (temp_env)
	{
		if (strncmp(temp_token, temp_env->content, i) == 0)
		{
			free(temp_env->content);
			temp_env->content = ft_strdup(token);
			free(temp_token);
			return (1);
		}
		temp_env = temp_env->next;
	}
	free(temp_token);
	return (0);
}

int		count_words(char *str)
{
	int			state;
	unsigned	wc;
	int			i;

	state = 0;
	wc = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && is_before(str, i, '\\') == 0)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			++wc;
		}
		i++;
	}
	return (wc);
}

char	*change_to_octal(int dec)
{
	char	*temp;

	temp = ft_utoa_base(dec, "01234567");
	return (temp);
}
