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

int		check_semicolon_pipe(char *line)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (line && line[i])
	{
		if (line[i] != ';' && line[i] != ' ' && line[i] != '<' && line[i] != '>'
			&& ft_strncmp(&line[i], ">>", 1) != 0 && line[i] != '|')
			status = 1;
		if ((line[i] == ';' && status == 0 && ft_check_surround_2(line, i)) ||
			(line[i] == '|' && status == 0 && ft_check_surround_2(line, i)))
			return (ft_errors_line(line[i]));
		if ((line[i] == ';' || line[i] == '|') && status == 1)
			status = 0;
		i++;
	}
	return (1);
}

int		check_line(char *line)
{
	if (check_semicolon_pipe(line) == 0)
		return (0);
	if (check_redirection(line) == 0)
		return (0);
	return (1);
}

int		ft_check_surround_2(char *token, int pos)
{
	int	right_dq;
	int	left_dq;
	int	right_sq;
	int	left_sq;

	right_sq = check_sq_right(token, pos);
	left_sq = check_sq_left(token, pos);
	right_dq = check_dq_right(token, pos);
	left_dq = check_dq_left(token, pos);
	if ((right_sq == 1 && left_sq == 1) ||
		(right_dq == 1 && left_dq == 1))
		return (0);
	else
		return (1);
}

char	*get_before_semicolon(char *line)
{
	int		i;
	char	*pipeline;

	i = 0;
	pipeline = ft_strdup("");
	while (line && line[i])
	{
		if (line[i] == ';' && ft_check_surround_2(line, i))
		{
			free(line);
			return (pipeline);
		}
		pipeline = add_char(pipeline, line[i]);
		i++;
	}
	free(line);
	return (pipeline);
}

char	*ft_parse_pipe(t_data *data, char *line, int i, char *token)
{
	char *temp;

	if (is_before(line, i, ' '))
		free(token);
	if (i > 0 && ft_isalnum(line[i - 1]) == 1)
		ft_lstadd_back(&data->tokens, ft_lstnew(token));
	data->is_pipe = 1;
	data->pipeline = get_before_semicolon(ft_substr(line, i + 1,
		ft_strlen(line) - i));
	temp = ft_substr(line, ft_strlen(data->pipeline) + i + 2,
		ft_strlen(line) - ft_strlen(data->pipeline));
	if (ft_strncmp(temp, "", 1) == 0)
	{
		free(temp);
		free(line);
		return (NULL);
	}
	free(line);
	return (temp);
}
