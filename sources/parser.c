/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/06 15:51:57 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_exec_cmd(t_shell *shell)
{
	pid_t 	pid;
	int		status;
	char	**cmd;
	
	if (access(ft_split(sstoken, ' ')[0], F_OK) == 0)
		sstoken = ft_split(sstoken, '/')[ft_find_lenght(ft_split(sstoken, '/')) - 1];
	if (ft_builtin(sstoken, shell))
	{	
		pid = fork();
		if (pid == 0)
		{
			cmd = ft_split(sstoken, ' ');
			status = execve(ft_pathfinder(cmd[0], shell->env), cmd, shell->env);
			exit(status);
		}
		else
		{
			waitpid(pid, &status, 0);
			shell->exitstatus = WEXITSTATUS(status);
			// printf("Stato di uscita: %d\n", shell->exitstatus);
		}
	}
	shell->last_operator = ssoperator;
	shell->token++;
	shell->operator++;
}

void	ft_switch_op(t_shell *shell)
{
	// if (!ft_is_subshell(shell->token))
	// 	ft_subshell();
	if (!ft_strcmp(*(shell->operator), "|"))
		ft_exec_pipe(shell, ft_count_pipe(shell));
	else if (!ft_strcmp(*(shell->operator), "||"))
		ft_or(shell);
	else if (!ft_strcmp(*(shell->operator), "&&"))
		ft_and(shell);
	else if (*(shell->operator) == NULL && sstoken != NULL)
		ft_exec_cmd(shell);
	
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
		token = ft_strip(&token);
		operator = getcmd(shell->cmd, shell->env);
		operator = ft_strip(&operator);
		shell->token = ft_addelement(shell->token, token);
		shell->operator = ft_addelement(shell->operator, operator);
	}
}

void	ft_start(t_shell *shell)
{
	ft_creatematrix(shell);
	shell->operator_temp = shell->operator;
	shell->token_temp = shell->token;
	while(sstoken)
		ft_switch_op(shell);
	free(shell->cmd);
	free_matrix(shell->token_temp);
	free_matrix(shell->operator_temp);
}
