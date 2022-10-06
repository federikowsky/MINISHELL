/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:34:45 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/06 14:28:33 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_or(t_shell *shell)
{
	if (shell->exitstatus == 1 && ft_strcmp(*(shell->operator + 1), "|") == 0)
	{
		shell->operator++;
		ft_exec_pipe(shell, ft_count_pipe(shell));
	}
	// else if (ft_strcmp(shell->last_operator, "||") != 0 || shell->exitstatus != 0)
	else if (shell->exitstatus != 0)
		ft_exec_cmd(shell);
	if (shell->exitstatus == 0)
	{
		if (ft_strcmp(ssoperator, "||") == 0)
			shell->operator++;
		while (ft_strcmp(ssoperator, "|") == 0 || ft_strcmp(ssoperator, "||") == 0)
		{
			shell->token++;
			shell->operator++;
		}
		if (sstoken)
			shell->token++;
	}
}

void	ft_and(t_shell *shell)
{
	if (ft_strcmp(*(shell->operator + 1), "|") == 0)
	{
		shell->operator++;
		ft_exec_pipe(shell, ft_count_pipe(shell));
	}
	else if (shell->exitstatus != 0 || shell->exitstatus == 0)
		ft_exec_cmd(shell);
	if (shell->exitstatus == 0 && sstoken != NULL)
	{
		if (*(shell->operator) == NULL)
			ft_exec_cmd(shell);
		else 
			ft_switch_op(shell);
	}
	else if (shell->exitstatus == 1)
	{
		while (ft_strcmp(ssoperator, "&&") == 0)
		{
			shell->token++;
			shell->operator++;
		}
		if (sstoken)
			shell->token++;
	}
}