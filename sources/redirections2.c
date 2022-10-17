/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:14:13 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/17 14:13:26 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_redir_in_exec(char * token, t_shell *shell)
{
	char	**cmd;

	if (ft_builtin(token, shell))
	{	
		cmd = ft_split(token, ' ');
		execve(ft_pathfinder(cmd[0], shell->env), cmd, shell->env);
		exit(127);
	}
	exit(0);
}

static void	ft_in_redir(char *cmd, t_shell *shell)
{
	int		filein;
	int		status;
	int		fd;
	pid_t 	pid;

	fd = open(sstoken, O_RDONLY, 0777);
	filein = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	pid = fork();
	if (!pid)
		ft_redir_in_exec(cmd, shell);
	else
		waitpid(pid, &status, 0);
	shell->exitstatus = WEXITSTATUS(status);
	dup2(filein, STDIN_FILENO);
	close(filein);
}

void	ft_left_redir(t_shell *shell)
{
	char	*curr_cmd;

	curr_cmd = sstoken;
	while (sstoken && !ft_strcmp(*(shell->operator), "<"))
	{
		shell->token++;
		ft_in_redir(curr_cmd, shell);
		shell->operator++;
	}
	if (sstoken)
		shell->token++;
}


