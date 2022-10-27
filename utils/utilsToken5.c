/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:54:34 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/27 16:55:26 by agenoves         ###   ########.fr       */
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
			return (-1);
	}
	if (cmd[i] == 39)
	{
		if (ft_quoteparent(cmd + i, 39) != 0)
			i += ft_quoteparent(cmd + i, 39);
		else
			return (-1);
	}
	return (i);
}
