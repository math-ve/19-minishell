/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:13:45 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:39:19 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_error_eof(char c, char *new_str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'", 2);
	errno = 1;
	free(new_str);
	return (NULL);
}

int		error_redir(void)
{
	ft_putstr_fd("minishell: syntax error near ", 2);
	ft_putstr_fd("unexpected token `newline'\n", 2);
	errno = 1;
	return (0);
}
