/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:38:18 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:49:49 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*** ret 1 if option OK || ret 0 if option NOT OK
*** IF -nnne IT SHOULD WORK
*/

int		check_option(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	if (token[i] == '-' && token[i + 1] == 'n')
	{
		i += 2;
		while (token[i])
		{
			if (token[i] != 'n' && (ft_isalpha(token[i]) == 0))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

char	*ft_echo_2(t_list *temp, int new_line)
{
	char	*str_to_print;

	str_to_print = NULL;
	while (temp)
	{
		while (new_line && !ft_strncmp(temp->content, "-n", 1))
			temp = temp->next;
		if (str_to_print)
			str_to_print = ft_strjoin_free(str_to_print, temp->content);
		else
			str_to_print = ft_strdup(temp->content);
		if (temp->next)
			str_to_print = add_char(str_to_print, ' ');
		temp = temp->next;
		while (temp && new_line && !ft_strncmp(temp->content, "-n", 1))
		{
			str_to_print = ft_strjoin_free(str_to_print, temp->content);
			if (temp->next)
				str_to_print = add_char(str_to_print, ' ');
			temp = temp->next;
		}
	}
	return (str_to_print);
}

char	*no_newline(char *str_to_print, int new_line)
{
	if (!new_line)
	{
		if (str_to_print)
			str_to_print = add_char(str_to_print, '\n');
		else
			str_to_print = ft_strdup("\n");
	}
	return (str_to_print);
}

int		ft_echo(t_data *data)
{
	t_list	*temp;
	int		new_line;
	char	*str_to_print;

	temp = data->tokens->next;
	str_to_print = NULL;
	if (data->was_pipe)
		dup2(data->stdout_cpy, 1);
	if (temp)
		errno = 0;
	new_line = 0;
	if (temp && (new_line = check_option(temp->content)))
		temp = temp->next;
	str_to_print = ft_echo_2(temp, new_line);
	str_to_print = no_newline(str_to_print, new_line);
	if (data->is_pipe)
		ft_pipe(data, str_to_print);
	else
		ft_putstr_fd(str_to_print, 1);
	free(str_to_print);
	return (0);
}
