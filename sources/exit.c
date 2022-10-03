/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:41:06 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/03 14:48:09 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_exit(t_shell *shell)
// {
// 	int	i;
// 	int	check;

// 	check = 0;
// 	i = 0;
// 	printf("exit\n");
// 	if (ft_find_lenght(shell->cmds) > 2)
// 		printf("too many arguments\n");
// 	else if (ft_find_lenght(shell->cmds) == 2)
// 	{
// 		while (shell->cmds[1][i])
// 		{
// 			if (!ft_isdigit(shell->cmds[1][i]))
// 			{
// 				check = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (check)
// 			printf("minishell: exit: %s: numeric argument required\n", \
// 			shell->cmds[1]);
// 	}
// 	exit(0);
// }