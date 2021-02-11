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

int		ft_increment(int *i, char *line, char c)
{
	int count;

	count = 0;
	while (line[(*i)] == c)
	{
		count++;
		(*i)++;
	}
	return (count);
}

int		count_redirection_left(char *line)
{
	int	i;
	int	count;

	i = 0;
	while (line[i++])
	{
		count = 0;
		if (line[i] == '<' && ft_check_surround_2(line, i))
		{
			count = ft_increment(&i, line, '<');
			if (count == 3)
				return (ft_errors_line('<'));
			if (count > 3)
				return (ft_errors_line2("<<"));
			while (line[i] == ' ')
				i++;
			if (line[i] == '<')
			{
				if (line[i + 1] == '<')
					return (ft_errors_line2("<<"));
				return (ft_errors_line('<'));
			}
		}
	}
	return (1);
}

int		count_redirection_right(char *line)
{
	int	i;
	int	count;

	i = 0;
	while (line[i++])
	{
		count = 0;
		if (line[i] == '>' && ft_check_surround_2(line, i))
		{
			count = ft_increment(&i, line, '>');
			if (count == 3)
				return (ft_errors_line('>'));
			if (count > 3)
				return (ft_errors_line2(">>"));
			while (line[i] == ' ')
				i++;
			if (line[i] == '>')
			{
				if (line[i + 1] == '>')
					return (ft_errors_line2(">>"));
				return (ft_errors_line('>'));
			}
		}
	}
	return (1);
}

int		check_redirection(char *line)
{
	int	i;
	int	status;

	i = 0;
	status = 1;
	if ((count_redirection_right(line) == 0) ||
		(count_redirection_left(line) == 0))
		return (0);
	while (line && line[i++])
	{
		if ((line[i] == '>' && line[i + 1] != '>' && status == 1) ||
			(line[i] == '<' && line[i + 1] != '<' && status == 1))
			status = 0;
		else if ((line[i] == '>' || line[i] == '<') && status == 0)
		{
			if (line[i] == '>' && line[i + 1] == '>')
				return (ft_errors_line2(">>"));
			else if (line[i] == '<' && line[i + 1] == '<')
				return (ft_errors_line2("<<"));
			return (ft_errors_line(line[i]));
		}
		if (line[i] != '<' && line[i] != '>' && line[i] != ' ')
			status = 1;
	}
	return (1);
}

int		check_pipes(char *line)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (line && line[i])
	{
		if (line[i] != '|' && line[i] != ';' && line[i] != ' ' &&
			line[i] != '<' && line[i] != '>'
			&& ft_strncmp(&line[i], ">>", 1) != 0)
			status = 1;
		else if (line[i] == '|' && status == 0)
			return (ft_errors_line(line[i]));
		else if ((line[i] == '|' || line[i] == ';') && status == 1)
			status = 0;
		i++;
	}
	return (1);
}
