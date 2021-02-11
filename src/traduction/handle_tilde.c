/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:12:32 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 15:16:29 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		*handle_tilde(t_data *data, char *token)
{
	char	*new_str;
	char	*temp;

	if ((token[0] == '~' && !token[1]) || (token[0] == '~' && token[1] == '/'))
	{
		new_str = get_value_env(data, "HOME");
		temp = ft_substr(token, 1, ft_strlen(token) - 1);
		new_str = ft_strjoin_free_all(new_str, temp);
		return (new_str);
	}
	return (token);
}
