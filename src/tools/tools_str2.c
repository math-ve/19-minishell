/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_str2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 14:22:32 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 18:36:35 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_empty_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isprint(str[i]) == 1 && str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (s2 == NULL || s1 == NULL)
		return (NULL);
	if (!(dest = malloc((ft_strlen((char*)s1) +
		ft_strlen((char*)s2)) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(s1);
	return (dest);
}

char	*ft_strjoin_free_all(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	if (s2 == NULL || s1 == NULL)
		return (NULL);
	if (!(dest = (char *)malloc((ft_strlen((char*)s1) +
		ft_strlen((char*)s2)) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	free(s1);
	free(s2);
	return (dest);
}

int		is_before(char *token, int pos, char c)
{
	if (pos > 0)
	{
		if (token[pos - 1] == c)
			return (1);
	}
	return (0);
}

char	*check_backslash(char *env_after_egal)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = strdup("");
	while (env_after_egal[i])
	{
		if (env_after_egal[i] == '\\' &&
			is_before(env_after_egal, i, '\\') == 0)
			new_str = add_char(new_str, '\\');
		else if (env_after_egal[i] == '\'')
			new_str = add_char(new_str, '\\');
		else if (env_after_egal[i] == '\\' && env_after_egal[i + 1] == '\\')
			new_str = add_char(new_str, '\\');
		else if (env_after_egal[i] == '\\' && env_after_egal[i + 1] != '\\'
			&& is_before(env_after_egal, i, '\\'))
			new_str = add_char(new_str, '\\');
		new_str = add_char(new_str, env_after_egal[i]);
		i++;
	}
	free(env_after_egal);
	return (new_str);
}
