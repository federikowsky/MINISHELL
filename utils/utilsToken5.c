/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:54:34 by agenoves          #+#    #+#             */
/*   Updated: 2022/11/02 19:30:38 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_checkall(char *cmd, int i)
{
	if (cmd[i] == 34)
	{
		if (ft_quoteparent(cmd + i, 34) != 0)
			i += ft_quoteparent(cmd + i, 34);
		else
			return (-2);
	}
	if (cmd[i] == 39)
	{
		if (ft_quoteparent(cmd + i, 39) != 0)
			i += ft_quoteparent(cmd + i, 39);
		else
			return (-2);
	}
	return (i);
}
