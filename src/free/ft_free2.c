/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 11:26:40 by mvan-eyn          #+#    #+#             */
/*   Updated: 2021/01/31 19:24:51 by hbuisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_bin(char **bin_array, char **token_array, char **env_array)
{
	free_array(env_array);
	free_array(token_array);
	free_array(bin_array);
}

void	free_norme(t_data *data, char *temp)
{
	free_list(data);
	free(temp);
}
