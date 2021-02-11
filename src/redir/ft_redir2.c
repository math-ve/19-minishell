/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:10:18 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:54:06 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_redir_line(char *redir_line)
{
	char	*new_str;
	int		i;

	i = 0;
	while (redir_line[i] && redir_line[i] != ';' && redir_line[i] != '|')
		i++;
	if (redir_line[i] == ';' || redir_line[i] == '|')
	{
		new_str = ft_substr(redir_line, i, ft_strlen(redir_line) - i);
		return (new_str);
	}
	return (NULL);
}

char	*isolate_file_name(t_data *data)
{
	char	*file_name;
	char	*temp;
	int		i;

	i = 0;
	file_name = ft_strdup("");
	while (data->redir_line[i] && data->redir_line[i] == ' ')
		i++;
	while (data->redir_line[i] && data->redir_line[i] != ' ' &&
		data->redir_line[i] != ';' && data->redir_line[i] != '|')
	{
		file_name = add_char(file_name, data->redir_line[i]);
		i++;
	}
	while (data->redir_line[i] && data->redir_line[i] == ' ')
		i++;
	temp = check_redir_line(data->redir_line);
	free(data->redir_line);
	data->redir_line = temp;
	return (file_name);
}

int		delete_redir_tokens(t_data *data, char *token)
{
	t_list	*temp_token;
	t_list	*prev_token;

	temp_token = data->tokens;
	if (temp_token != NULL &&
		ft_strncmp(temp_token->content, token, ft_strlen(token)) == 0)
	{
		data->tokens = temp_token->next;
		free(temp_token->content);
		free(temp_token);
		return (1);
	}
	while (temp_token &&
		ft_strncmp(temp_token->content, token, ft_strlen(token)) != 0)
	{
		prev_token = temp_token;
		temp_token = temp_token->next;
	}
	if (temp_token == NULL)
		return (0);
	prev_token->next = temp_token->next;
	free(temp_token->content);
	free(temp_token);
	return (1);
}

int		dispatch_redir(char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(token, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(token, "<", 1) == 0)
		return (3);
	return (0);
}
