/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/11/03 19:36:14 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_pipe(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_strcmp((shell->op)[i], "|") == 0)
	{
		count++;
		i++;
	}
	return (count);
}

void	open_pipe(int pipes[], int no_pipes)
{
	int	i;

	i = -1;
	while (++i < no_pipes)
		pipe(pipes + i * 2);
}

void	close_pipe(int pipes[], int no_pipes)
{
	int	j;

	j = 0;
	while (j < 2 * no_pipes)
		close(pipes[j++]);
}

void	ft_pipe1(t_shell *shell, int pipes[], int i, int nb_pipe)
{
	if (*(shell->tok + 1) != NULL && !(!ft_strcmp(*(shell->op), ">") || !ft_strcmp(*(shell->op), ">>")))
		dup2(pipes[i + 1], STDOUT_FILENO);
	if (i != 0)
		dup2(pipes[i - 2], STDIN_FILENO);
	close_pipe(pipes, nb_pipe);
	if (ft_is_subshell(&(*(shell->tok))))
		ft_subshell(shell, *(shell->tok));
	if (!ft_strcmp(*(shell->op), ">") || !ft_strcmp(*(shell->op), ">>"))
	{
		ft_exec_cmd(shell);
		exit(0);
	}
	else if (ft_strchr(*(shell->tok), '*'))
	{
		ft_wild(shell);
		exit(0);
	}
	else
		ft_exec_cmd_fork(shell);
}

void	ft_pipe2(t_shell *shell, int *i, int *j)
{
	*i += 2;
	if (ft_strcmp(*(shell->op), "<"))
		shell->tok++;
	if (*j)
	{
		shell->last_operator = *(shell->op);
		shell->op++;
	}
	if (*(shell->tok) && *(shell->tok)[0] == '\0')
		*j = 0;
}

void	ft_pipe3(t_shell *shell, int pipes[], int nb_pipe, int i)
{
	int		status;

	close_pipe(pipes, nb_pipe);
	while (i-- > 0)
		waitpid(-1, &status, 0);
	if (!ft_strcmp(*(shell->op), "<"))
		ft_left_redir(shell);
	shell->exitstatus = WEXITSTATUS(status);
	shell->prev_exitstatus = shell->exitstatus;
	if (shell->is_subshell)
		exit(shell->exitstatus);
}
void	ft_exec_pipe(t_shell *shell, int nb_pipe)
{
	int		i;
	int		j;
	int		pipes[2 * nb_pipe];
	pid_t	pid;

	i = 0;
	j = nb_pipe + 1;
	open_pipe(pipes, nb_pipe);
	while (*(shell->tok) && j-- > 0)
	{
		pid = fork();
		if (pid == 0)
			ft_pipe1(shell, pipes, i, nb_pipe);
		ft_pipe2(shell, &i, &j);
	}
	ft_pipe3(shell, pipes, nb_pipe, i);
}
