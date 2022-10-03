/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:34:45 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/03 19:10:09 by agenoves         ###   ########.fr       */
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
	}
	shell->token++;
	// ft_exec_cmd(shell);
}

void	ft_and(t_shell *shell)
{
	ft_exec_cmd(shell);
	if (shell->exitstatus == 0)
	{
		shell->token++;
		shell->operator++;
		ft_switch_op(shell);
	}
}