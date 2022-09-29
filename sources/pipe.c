/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/09/23 17:02:45 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void open_pipe(int pipes[], int no_pipes)
{
	int i;
	
	i = -1;
	while (++i < no_pipes)
		pipe(pipes + i * 2);
}

void close_pipe(int pipes[], int no_pipes)
{   
    int j;

    j = 0;
    while (j < 2 * no_pipes)
        close(pipes[j++]);
}

void exec_pipe(t_shell *shell)
{
	int i;
	int j;
	int pipes[2 * (shell->cmd_count - 1)];
	int status;
	
	i = 0;
	j = 0;
	open_pipe(pipes, shell->cmd_count - 1);
	while (shell->pipes[j])
	{
		if (fork() == 0)
		{
			if (shell->pipes[j + 1] != NULL)
				dup2(pipes[i + 1], STDOUT_FILENO);
			if (i != 0)
				dup2(pipes[i - 2], STDIN_FILENO);
			close_pipe(pipes, shell->cmd_count - 1);
			shell->cmd = shell->pipes[j];
			/* handle execution of command here: */
			// ft_parser(shell, shell->pipes[j]);
		}
		else 
			printf("%s\n", strerror(errno));
		i += 2;
		j++;
	}
	close_pipe(pipes, shell->cmd_count - 1);
	while (i-- > 0)
		wait(NULL);
}

void exec_cmd(t_shell *shell)
{
	shell->cmds = ft_cmd_count(shell->cmd);
	shell->pipes = ft_split(shell->cmd, '|');
	exec_pipe(shell);
}