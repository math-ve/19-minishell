/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:46:18 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:20:00 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_parse_redir(t_data *data, char *line, int *i, char *token_prev)
{
	char *token;

	data->is_redir = 1;
	if ((*i) > 0 && ft_isalnum(line[(*i) - 1]) == 1)
		ft_lstadd_back(&data->tokens, ft_lstnew(token_prev));
	else
		free(token_prev);
	if (line[(*i) + 1] == '>')
	{
		token = ft_strdup(">>");
		(*i)++;
		(*i)++;
	}
	else if (line[(*i)] == '>' && line[(*i) + 1] != '>')
	{
		token = ft_strdup(">");
		(*i)++;
	}
	else if (line[(*i)] == '<')
	{
		token = ft_strdup("<");
		(*i)++;
	}
	return (token);
}

char	*ft_parse_semicolon(t_data *data, char *line, char *token, int i)
{
	char *temp;

	if (ft_strncmp(token, "", 1) != 0)
		ft_lstadd_back(&data->tokens, ft_lstnew(ft_strdup(token)));
	save_underscore(data, token);
	temp = ft_substr(line, i + 1, ft_strlen(line) - i);
	free(line);
	free(token);
	return (temp);
}

int		is_token_content(char *line, int i)
{
	if ((line[i] && line[i] != ' ' && line[i] != '\t') ||
		(line[i] && (line[i] == ' ' && is_before(line, i, '\\'))))
		return (1);
	else
		return (0);
}

int		ft_fill_token(t_data *data, char *line, int *i)
{
	while (is_token_content(line, (*i)))
	{
		if (line[(*i)] && line[(*i)] == '\'' && is_before(line, (*i), '\\')
			== 0)
			data->token = add_sq(data->token, line, i);
		else if (line[(*i)] && line[(*i)] == '\"' &&
			is_before(line, (*i), '\\') == 0)
			data->token = add_dq(data->token, line, i);
		else if (line[(*i)] == '|' && is_before(line, (*i), '\\') == 0)
			return (1);
		else if ((line[(*i)] == '>' && is_before(line, (*i), '\\') == 0) ||
			(line[(*i)] == '<' && is_before(line, (*i), '\\') == 0))
		{
			data->token = ft_parse_redir(data, line, i, data->token);
			return (2);
		}
		else if (line[(*i)] != ';' ||
			(line[(*i)] == ';' && is_before(line, (*i), '\\')))
			data->token = add_char(data->token, line[(*i)]);
		else if (line[(*i)] == ';' && is_before(line, (*i), '\\') == 0)
			return (3);
		if (data->token)
			(*i)++;
	}
	return (4);
}

char	*ft_parser(char *line, t_data *data)
{
	int		i;
	int		ret;

	i = 0;
	if (check_line(line) == 0)
		return (free_return_null(line));
	while (line[i])
	{
		data->token = ft_strdup("");
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		ret = ft_fill_token(data, line, &i);
		if (ret == 1)
			return (ft_parse_pipe(data, line, i, data->token));
		else if (ret == 3)
			return (ft_parse_semicolon(data, line, data->token, i));
		if (data->token && ft_strncmp(data->token, "", 1) != 0)
			ft_lstadd_back(&data->tokens, ft_lstnew(data->token));
		else
			free(data->token);
	}
	if (!data->was_pipe)
		free(line);
	return (NULL);
}
