/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:41:06 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/05 13:41:27 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_shell *shell)
{
	int		i;
	int		check;
	char	**cmds;

	cmds = ft_split(sstoken, ' ');
	check = 0;
	i = 0;
	printf("exit\n");
	if (ft_find_lenght(cmds) > 2)
		printf("too many arguments\n");
	else if (ft_find_lenght(cmds) == 2)
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
	}
	exit(0);
}