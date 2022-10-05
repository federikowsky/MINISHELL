/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/05 13:36:36 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_cmd_fork(t_shell *shell)
{
	char	**cmd;

	shell->exitstatus = 0;
	if (ft_builtin(sstoken, shell))
	{	
		cmd = ft_split(sstoken, ' ');
		execve(ft_pathfinder(cmd[0], shell->env), cmd, shell->env);
			shell->exitstatus = 1;
	}
	exit(0);
}

int ft_count_pipe(t_shell * shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_strcmp((shell->operator)[i], "|") == 0)
	{
		count++;
		i++;
	}
	return (count);
}

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

void ft_exec_pipe(t_shell *shell, int nb_pipe)
{
	int i;
	int pipes[2 * nb_pipe];
	int status;
	
	i = 0;
	open_pipe(pipes, nb_pipe);
	while (sstoken)
	{
		if (fork() == 0)
		{
			if (*(shell->token + 1) != NULL)
				dup2(pipes[i + 1], STDOUT_FILENO);
			if (i != 0)
				dup2(pipes[i - 2], STDIN_FILENO);
			close_pipe(pipes, nb_pipe);
			ft_exec_cmd_fork(shell);
		}
		i += 2;
		shell->token++;
		shell->operator++;
	}
	close_pipe(pipes, nb_pipe);
	while (i-- > 0)
        wait(&status);
		if (WIFEXITED(status))
			printf("Stato di uscita: %d\n", WEXITSTATUS(status));
}

