/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:41:06 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 19:37:36 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *shell)
{
	int		i;
	int		check;
	char	**cmds;

	cmds = ft_split(*(shell->tok), ' ');
	check = 0;
	i = 0;
	printf("exit\n");
	if (ft_mat_lenght(cmds) > 2)
		printf("too many arguments\n");
	else if (ft_mat_lenght(cmds) == 2)
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
			printf("minishell: exit: %s: numeric argument required\n", \
			cmds[1]);
		exit(ft_atoi(cmds[1]));
	}
	exit(0);
}
