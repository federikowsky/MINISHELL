/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:41:06 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/27 10:47:31 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *shell, int check, int i)
{
	char	**cmds;

	cmds = ft_split(*(shell->tok), ' ');
	printf("exit\n");
	if (matln(cmds) > 2)
		printf("too many arguments\n");
	else if (matln(cmds) == 2)
	{
		while (cmds[1][i])
		{
			if (!ft_isdigit(cmds[1][i]))
			{
				check = 1;
				break ;
			}
			i++;
		}
		if (check)
			printf("minishell: exit: %s: numeric arg required\n", cmds[1]);
		exit(ft_atoi(cmds[1]));
	}
	exit(0);
}
