/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/05 12:39:12 by md-aless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exec_cmd(t_shell *shell, int fd[2])
{
	pid_t	pid;
	int		status;
	
	if (ft_builtin(sstoken, shell))
	{
		pid = fork();
		if (pid == 0)
		{
			if (fd != NULL)
			{
				// close(fd[0]);
				close(fd[1]);
				dup2(fd[1], 1);
			}
			execve(ft_pathfinder(sstoken, shell->env), \
				ft_split(sstoken, ' '), shell->env);
			exit(EXIT_FAILURE);
		}
		if (fd != NULL)
		{
			// close(fd[1]);
			close(fd[0]);
			dup2(fd[0], 0);
		}
		while(waitpid(pid, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				shell->exitstatus = WEXITSTATUS(status);
		}
	}
	shell->token++;
	shell->operator++;
}

void	ft_switch_op(t_shell *shell)
{
	// if (!ft_is_subshell(shell->token))
	// 	ft_subshell();
	if (!ft_strcmp(*(shell->operator), "|"))
		ft_pipe(shell);
	else if (!ft_strcmp(*(shell->operator), "||"))
		ft_or(shell);
	else if (!ft_strcmp(*(shell->operator), "&&"))
		ft_and(shell);
	else if (*(shell->operator) == NULL && sstoken != NULL)
		ft_exec_cmd(shell, NULL);
	
}

char	*getcmd(char *s, char **envp)
{
	int				start;
	char			*temp;
	static int		i = 0;
	static int		in_cmd_mode = 1;

	if (i == -2)
	{
		i = 0;
		return (NULL);
	}
	start = getcmd_aux(s, &i);
	while (s[i])
	{
		if (in_cmd_mode && ft_has(s[i], "(\"'"))
		{
			in_cmd_mode = 0;
			i = findparenth(s, start) + 1;
			return (ft_arg_check(getsub(s, start + 1, i - 1), envp));
		}
		// else if (in_cmd_mode && !ft_isdigit(s[i]) && !ft_isalpha(s[i]) && !ft_has(s[i], " =-.*"))
		else if (in_cmd_mode && !ft_isdigit(s[i]) && !ft_isalpha(s[i]) && ft_has(s[i], "|&"))
		{
			in_cmd_mode = 0;
			// getsub(s, start, i);
			return (ft_arg_check(getsub(s, start, i), envp));
		}
		else if (!in_cmd_mode && !ft_has(s[i], "|&"))
		{
			in_cmd_mode = 1;
			return (getsub(s, start, i));
		}
		i++;
	}
	i = -2;
	temp = getsub(s, start, ft_strlen(s));
	if (*temp)
		return (ft_arg_check(temp, envp));
	return (NULL);
}

void ft_creatematrix(t_shell *shell)
{
	char	*token;
	char	*operator;
	token = " ";
	operator = " ";
	while (token != NULL && operator != NULL)
	{
		token = getcmd(shell->cmd, shell->env);
		operator = getcmd(shell->cmd, shell->env);
		shell->token = ft_addelement(shell->token, token);
		shell->operator = ft_addelement(shell->operator, operator);
	}
}

void	ft_start(t_shell *shell)
{
	ft_creatematrix(shell);
	// ft_print_mat(shell->token);
	// ft_print_mat(shell->operator);
	shell->operator_temp = shell->operator;
	shell->token_temp = shell->token;
	while(sstoken)
	{
		ft_switch_op(shell);
	}
	free(shell->cmd);
	free_matrix(shell->token_temp);
	free_matrix(shell->operator_temp);
}
