/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 03:16:01 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 19:28:46 by agenoves         ###   ########.fr       */
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
	if ((!ft_strcmp(ssoperator, ">") || !ft_strcmp(ssoperator, ">>")) && shell->redirec)
	{
		dup2(shell->redirec, STDOUT_FILENO);
		close(shell->redirec);
	}
	if (access(ft_split(sstoken, ' ')[0], F_OK) == 0)
		sstoken = ft_split(sstoken, '/')[ft_mat_lenght(ft_split(sstoken, '/')) - 1];
	if (ft_builtin(sstoken, shell))
	{	
		pid = fork();
		if (pid == 0)
		{
			cmd = ft_split(sstoken, ' ');
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
	if ((!ft_strcmp(ssoperator, ">") || !ft_strcmp(ssoperator, ">>")) && shell->redirec)
	{
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
	}
	shell->last_operator = ssoperator;
	shell->token++;
	shell->operator++;
}
