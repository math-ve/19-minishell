/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:16:12 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:56:01 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		check_valid_exit(char *token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i])
	{
		if (ft_isalnum(token[i]))
		{
			if ((is_before(token, i, '+') && is_before(token, i - 1, '+')) ||
				(is_before(token, i, '-') && is_before(token, i - 1, '-')) ||
				is_before(token, i, '_'))
				return (0);
			j = 0;
			while (token[i + j])
			{
				if (ft_isdigit(token[i + j]) == 0 &&
					token[i + j] != ' ' &&
					token[i + j] != '\t')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

char	*parse_nbr(char *nbr)
{
	char	*parsed_nbr;
	int		i;

	i = 0;
	parsed_nbr = ft_strdup("");
	if (nbr[0] == '-')
		i++;
	while (nbr[i] == '0')
		i++;
	while (ft_isdigit(nbr[i]))
		parsed_nbr = add_char(parsed_nbr, nbr[i++]);
	return (parsed_nbr);
}

int		check_arg(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_isdigit(token[i]) == 0
			&& token[i] != '-'
			&& token[i] != '+'
			&& ft_isspace(token[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_exit(t_data *data)
{
	t_list	*temp_token;

	if (data->is_pipe)
		return (0);
	if (data->tokens->next)
	{
		temp_token = data->tokens->next;
		if (check_arg(temp_token->content) == 0)
			ft_error_exit(data, 2);
		if (temp_token->next != NULL)
			ft_error_exit(data, 1);
		if (check_valid_exit(temp_token->content))
		{
			if (check_int_valid(temp_token->content) == 0)
				exit(ft_atoi((char *)temp_token->content));
			ft_error_exit(data, 2);
		}
		else
			ft_error_exit(data, 2);
	}
	else
		exit(0);
	return (0);
}
