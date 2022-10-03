/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/03 19:14:19 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
	CMD:
		-1 Ultimo comando
		0  Primo comando
		1  Altri casi
*/

void	exec_pipe(t_shell *shell, int nb_cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("Error Piping!");
		return ;
	}
	if (nb_cmd != -1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	if (nb_cmd != 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}
	if (nb_cmd == -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	ft_exec_cmd(shell);
}

void	ft_pipe(t_shell *shell)
{
	static int	nb_cmd = 0;
	
	if (shell->operator == NULL)
	{
		nb_cmd = -1;
		exec_pipe(shell, nb_cmd);
		nb_cmd = 0;
	}
	else
	{
		exec_pipe(shell, nb_cmd);
		nb_cmd = 1;
	}
}
