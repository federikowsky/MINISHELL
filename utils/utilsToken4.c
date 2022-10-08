/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:37:59 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/08 18:43:03:02 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redir_check(char *cmd)
{
	int	i;
	i = 0;
	while (cmd[i] != '\0')
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || \
			(cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			if ((cmd[i + 1] == '>' && cmd[i + 2] == '>') || \
			(cmd[i + 1] == '<' && cmd[i + 2] == '<'))
			{
				perror("Redir Check Problem: Minishell");
				return (1);
			}
		}
		i++;
	}
	return (0);
}