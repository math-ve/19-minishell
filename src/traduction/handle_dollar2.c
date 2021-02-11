/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:13:20 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:50:43 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*ft_parse_token(char *token, int *i)
{
	char	*temp;

	temp = ft_strdup("");
	(*i)++;
	while (token[(*i)] && (ft_isalnum(token[(*i)]) || token[(*i)] == '_'))
	{
		temp = add_char(temp, token[(*i)]);
		(*i)++;
	}
	if (ft_strncmp(temp, "", 1))
		temp = add_char(temp, '=');
	return (temp);
}

char		*check_and_add(char *env_after_egal, int pos, int len, char *token)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	while (env_after_egal[i])
	{
		if ((env_after_egal[i] == ' ' && is_before(env_after_egal, i, ' ')
			&& i != 0) || (env_after_egal[i] == ' ' && i == 0 && pos == 0) ||
			(env_after_egal[i] == ' ' && env_after_egal[i + 1] == '\0' &&
				token[len] == '\0'))
		{
		}
		else
			new_str = add_char(new_str, env_after_egal[i]);
		i++;
	}
	return (new_str);
}

char		*check_space_dq(char *env_after_egal, char *token, int pos, int len)
{
	char	*new_str;

	new_str = ft_strdup("");
	if (check_dq_right(token, pos) == 0 && check_dq_left(token, pos) == 0)
	{
		free(new_str);
		new_str = check_and_add(env_after_egal, pos, len, token);
		if ((is_before(new_str, ft_strlen(new_str), ' ') &&
			token[len] == '\0') || (is_before(new_str, ft_strlen(new_str), ' ')
			&& token[len] == '$'))
			new_str = remove_last_space(new_str);
		free(env_after_egal);
		return (new_str);
	}
	free(new_str);
	return (env_after_egal);
}

int			ft_check_surround(char *token, int pos)
{
	int	right_dq;
	int	left_dq;
	int	right_sq;
	int	left_sq;

	right_sq = check_sq_right(token, pos);
	left_sq = check_sq_left(token, pos);
	right_dq = check_dq_right(token, pos);
	left_dq = check_dq_left(token, pos);
	if (((right_sq == 1 && left_sq == 1) && (left_dq == 0 && right_dq == 0)) ||
		((right_sq == 1 && left_sq == 1) && (left_dq == 1 && right_dq == 0)))
		return (0);
	else
		return (1);
}
