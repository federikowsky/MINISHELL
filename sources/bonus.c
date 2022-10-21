/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:34:45 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/21 12:12:59 by md-aless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_or(t_shell *shell)
{
	if (shell->exitstatus > 0 && !ft_strncmp(*(shell->operator + 1), "|", 1))
	{
		shell->operator++;
		ft_exec_pipe(shell, ft_count_pipe(shell));
	}
	if (shell->exitstatus > 0 || sslastop[0] == '\0' || \
		!ft_strcmp(sslastop, "&&"))
		ft_exec_cmd(shell);
	if (shell->exitstatus == 0)
	{
		if (ft_strcmp(ssoperator, "||") == 0)
			shell->operator++;
		while (ft_strcmp(ssoperator, "|") == 0 || \
			ft_strcmp(ssoperator, "||") == 0)
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
	// if (ft_strcmp(*(shell->operator + 1), "|") == 0 && sslastop[0] != '\0')
	if (ft_strcmp(*(shell->operator + 1), "|") == 0)
	{
		ft_exec_cmd(shell);
		ft_exec_pipe(shell, ft_count_pipe(shell));
	}
	if (sstoken)
		ft_exec_cmd(shell);
	if (shell->exitstatus == 0 && sstoken != NULL)
		ft_switch_op(shell);
	else if (shell->exitstatus > 0)
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