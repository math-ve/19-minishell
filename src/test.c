/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 21:37:10 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 14:40:38 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_test(t_data *data, char *line)
{
	while (line)
	{
		line = ft_program(line, data);
	}
	return (0);
}

void	print_list(t_list *list)
{
	t_list *temp;

	temp = list;
	while (temp)
	{
		ft_putstr_fd(temp->content, 2);
		write(2, ".\n", 2);
		temp = temp->next;
	}
}
