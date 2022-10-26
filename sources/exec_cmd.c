/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:01 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 20:53:51 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_cmd_fork(t_shell *shell)
{
	char	**cmd;

	shell->exitstatus = 0;
	if (ft_builtin(*(shell->tok), shell))
	{	
		cmd = ft_split(*(shell->tok), ' ');
		execve(ft_pathfinder(cmd[0], shell->env), cmd, shell->env);
		exit(127);
	}
	exit(0);
}

void ft_exec_cmd_aux(t_shell *shell, char *arg)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	char	**tok;
	
	tok = *(shell->tok);
	if (arg)
		tok = ft_strjoin(tok, arg);
	if (access(ft_split(tok, ' ')[0], F_OK) == 0)
		tok = ft_split(tok, '/')[ft_mat_lenght(ft_split(tok, '/')) - 1];
	if (ft_builtin(tok, shell))
	{	
		pid = fork();
		if (pid == 0)
		{
			cmd = ft_split(tok, ' ');
			status = execve(ft_pathfinder(cmd[0], shell->env), cmd, shell->env);
			exit(127);
		}
		else
		{
			waitpid(pid, &status, 0);
			shell->exitstatus = WEXITSTATUS(status);
			shell->prev_exitstatus = shell->exitstatus;
		}
	}
}

void	ft_exec_cmd(t_shell *shell)
{
	int		fileout;

	fileout = dup(STDOUT_FILENO);
	if ((!ft_strcmp(*(shell->op), ">") || !ft_strcmp(*(shell->op), ">>")) && shell->redirec)
	{
		dup2(shell->redirec, STDOUT_FILENO);
		close(shell->redirec);
	}
	ft_exec_cmd_aux(shell, NULL);
	if ((!ft_strcmp(*(shell->op), ">") || !ft_strcmp(*(shell->op), ">>")) && shell->redirec)
	{
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
	}
	shell->last_operator = *(shell->op);
	shell->tok++;
	shell->op++;
}
