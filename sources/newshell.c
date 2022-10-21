/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:01:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/21 16:15:36 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_subshell(t_shell *shell, char *s)
{
	pid_t	pid;
	t_shell	newshell;
	int		status;

	pid = fork();
	if (!pid)
	{
		ft_envhandle(shell->env, &newshell);
		newshell.home = ft_get_home(&newshell);
		sig_handling_set(1);
		newshell.operator = NULL;
		newshell.token = NULL;
		newshell.exitstatus = -1;
		newshell.cmd = ft_strdup(s);
		newshell.last_operator = "";
		newshell.fd_in = shell->fd_out;
		newshell.is_subshell = 1;
		exit(ft_start(&newshell));
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exitstatus = WEXITSTATUS(status);
		shell->token++;
		shell->operator++;
	}
}

void	ft_run_new_shell(t_shell *shell)
{
	char	**env_copy;
	int		status;
	pid_t	pid;
	char	*path;

	path = ft_strjoin(ft_get_pwd(shell), "/./minishell");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		env_copy = ft_mat_copy(shell->env);
		ft_increase_shlvl(&env_copy);
		execve(path, &shell->cmd, env_copy);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exitstatus = WEXITSTATUS(status);
		shell->token++;
	}
}