/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:34:45 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/03 23:39:21 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_or(t_shell *shell)
{
	ft_exec_cmd(shell);
	if (shell->exitstatus == 0)
	{
		while (ft_strcmp(*(shell->operator), "|") == 0)
		{
			shell->token++;
			shell->operator++;
		}
		shell->token++;
	}
	// ft_exec_cmd(shell);
}

void	ft_and(t_shell *shell)
{
	ft_exec_cmd(shell);
	if (*(shell->operator) == NULL && *(shell->token) != NULL)
		ft_exec_cmd(shell);
	else if (shell->exitstatus == 0 && *(shell->token) != NULL)
		ft_switch_op(shell);
	else if (shell->exitstatus != 0)
	{
		printf("Minishell: %s: Command not found\n", *(shell->token));
		*(shell->token) = NULL;
	}
}