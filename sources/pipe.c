/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/04 16:17:07 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	CMD:
		-1 Ultimo comando
		0  Primo comando
		1  Altri casi
*/

void	exec_pipe(t_shell *shell)
{
	int		fd[2];

	if (pipe(fd) == -1)
		perror("Pipe Failed");
	ft_exec_cmd(shell, fd);
}

void	ft_pipe(t_shell *shell)
{
	
	if (shell->operator == NULL)
		ft_exec_cmd(shell, NULL);
	else
		exec_pipe(shell);
}
