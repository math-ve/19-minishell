/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traduction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:12:32 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 14:52:11 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		**split_after_dollar_trad(char *token)
{
	char	**tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tokens = malloc(sizeof(char *) * (count_words(token) + 1))))
		return (NULL);
	tokens[count_words(token)] = NULL;
	while (token && token[i] && j < count_words(token))
	{
		tokens[j] = ft_strdup("");
		while (token && token[i] == ' ' && token[i])
			i++;
		while ((token && token[i] && token[i] != ' ') ||
			(token && token[i] == ' ' && token[i] && is_before(token, i, '\\')))
		{
			tokens[j] = add_char(tokens[j], token[i]);
			i++;
		}
		while (token && token[i] && token[i + 1] && token[i + 1] == ' ')
			tokens[j] = add_char(tokens[j], token[i++]);
		j++;
	}
	return (tokens);
}

void		last_token(t_list *temp_tokens, char **tokens, char *token)
{
	t_list	*prev_token;
	t_list	*new_token;
	int		i;

	new_token = NULL;
	i = 1;
	prev_token = temp_tokens;
	prev_token->content = ft_strdup(tokens[0]);
	while (tokens[i])
	{
		new_token = ft_lstnew(ft_strdup(tokens[i]));
		prev_token->next = new_token;
		prev_token = new_token;
		i++;
	}
	free(token);
	free_array(tokens);
}

void		ft_fill(char **tokens, t_list *prev_token, t_list *temp_tokens)
{
	t_list	*new_token;
	t_list	*next_tokens;
	int		i;

	i = 0;
	new_token = NULL;
	next_tokens = temp_tokens->next;
	while (tokens[i])
	{
		new_token = ft_lstnew(tokens[i]);
		prev_token->next = new_token;
		prev_token = new_token;
		free(new_token);
		i++;
	}
	prev_token->next = next_tokens;
	free_array(tokens);
}

void		fill_list_after_split(t_list *temp_tokens, char *token)
{
	t_list	*prev_token;
	char	**tokens;

	tokens = split_after_dollar_trad(token);
	if (temp_tokens->next)
		while (temp_tokens)
		{
			if (ft_strncmp(temp_tokens->content, token, ft_strlen(token)) == 0)
			{
				ft_fill(tokens, prev_token, temp_tokens);
				return ;
			}
			prev_token = temp_tokens;
			temp_tokens = temp_tokens->next;
		}
	else
		last_token(temp_tokens, tokens, token);
}

void		ft_traduction(t_data *data)
{
	t_list	*temp_token;

	temp_token = data->tokens;
	while (temp_token)
	{
		temp_token->content =
			handle_dollar(data, temp_token->content);
		if (data->has_been_trad)
		{
			if (ft_strncmp(temp_token->content, "", 1))
				fill_list_after_split(temp_token, temp_token->content);
			data->has_been_trad = 0;
		}
		temp_token->content = handle_tilde(data, temp_token->content);
		temp_token->content = handle_quotes(temp_token->content);
		temp_token->content = handle_backslash(temp_token->content);
		temp_token = temp_token->next;
	}
}
