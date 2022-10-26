/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:01 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 19:37:39 by agenoves         ###   ########.fr       */
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

void	ft_exec_cmd(t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	**cmd;
	int		fileout;

	fileout = dup(STDOUT_FILENO);
	if ((!ft_strcmp(*(shell->op), ">") || !ft_strcmp(*(shell->op), ">>")) && shell->redirec)
	{
		dup2(shell->redirec, STDOUT_FILENO);
		close(shell->redirec);
	}
	if (access(ft_split(*(shell->tok), ' ')[0], F_OK) == 0)
		*(shell->tok) = ft_split(*(shell->tok), '/')[ft_mat_lenght(ft_split(*(shell->tok), '/')) - 1];
	if (ft_builtin(*(shell->tok), shell))
	{	
		pid = fork();
		if (pid == 0)
		{
			cmd = ft_split(*(shell->tok), ' ');
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
	if ((!ft_strcmp(*(shell->op), ">") || !ft_strcmp(*(shell->op), ">>")) && shell->redirec)
	{
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
	}
	shell->last_operator = *(shell->op);
	shell->tok++;
	shell->op++;
}
