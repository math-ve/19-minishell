/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-eyn <mvan-eyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:56:57 by mvan-eyn          #+#    #+#             */
/*   Updated: 2020/12/01 14:08:34 by mvan-eyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (alst && *alst && new)
	{
		tmp = *alst;
		while (new && tmp && tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
	}
	else if (alst)
	{
		*alst = new;
	}
}
