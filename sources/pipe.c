/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/08 18:52:2:15 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void ft_debug(t_shell *shell, int pipes[], int i)
{
	if (fork() == 0)
	{	
		// ft_putstr_fd("comando corrente: ", shell->fd_debug);
		// ft_putstr_fd(sstoken, shell->fd_debug);
		// ft_putendl_fd(" ", shell->fd_debug);
		ft_putstr_fd("stdin: ", shell->fd_debug);
		ft_putstr_fd(ft_itoa(shell->fd_in), shell->fd_debug);
		ft_putstr_fd("     ", shell->fd_debug);
		
		ft_putstr_fd("stdout: ", shell->fd_debug);
		ft_putendl_fd(ft_itoa(shell->fd_out), shell->fd_debug);
		
		ft_putstr_fd("pipe_out: ", shell->fd_debug);
		ft_putstr_fd(ft_itoa(pipes[i + 1]), shell->fd_debug);
		ft_putstr_fd("     ", shell->fd_debug);
		
		ft_putstr_fd("pipe_in: ", shell->fd_debug);
		if (i != 0)
			ft_putendl_fd(ft_itoa(pipes[i - 2]), shell->fd_debug);
		else
			ft_putendl_fd("-1", shell->fd_debug);
		ft_putendl_fd(" ", shell->fd_debug);
		_exit(0);
	}
	else
		wait(NULL);

}

void ft_exec_pipe(t_shell *shell, int nb_pipe)
{
	int 	i;
	int		j;
	int 	pipes[2 * nb_pipe];
	int 	status;
	pid_t	pid;
	
	i = 0;
	j = nb_pipe + 1;
	open_pipe(pipes, nb_pipe);
	ft_putendl_fd("ESEGUO PIPE", shell->fd_debug);
	while (sstoken && j-- > 0)
	{
		int newin;
		pid = fork();
		if (pid == 0)
		{
			ft_debug(shell, pipes, i);	
			if (ft_has((*(shell->operator + 1))[0], ">"))
				dup2(shell->redirec, STDOUT_FILENO);
			else if (*(shell->token + 1) != NULL)
				dup2(pipes[i + 1], STDOUT_FILENO);
			if (shell->fd_in)
			{
				newin = dup(shell->fd_in);
				dup2(newin, STDIN_FILENO);
				shell->fd_in = 0;
			}
			else if (i != 0)
				dup2(pipes[i - 2], STDIN_FILENO);
			close_pipe(pipes, nb_pipe);
			if (ft_is_subshell(sstoken))
				ft_subshell(shell, sstoken);	
			else
				ft_exec_cmd_fork(shell);
		}
		i += 2;
		shell->token++;
		shell->fd_out = pipes[i + 1];
		if (j)
		{
			shell->last_operator = ssoperator;	
			shell->operator++;
		}
	}
	close_pipe(pipes, nb_pipe);
	while (i-- > 0)
        waitpid(pid, &status, 0);
	shell->exitstatus = WEXITSTATUS(status);
	shell->prev_exitstatus = shell->exitstatus;	
}

