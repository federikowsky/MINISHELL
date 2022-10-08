/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/08 18:58:32 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_switch_op(t_shell *shell)
{
	if (ft_strcmp(sstoken, "./minishell") == 0)
		ft_run_new_shell(shell);
	if (!ft_strcmp(*(shell->operator), "|"))
		ft_exec_pipe(shell, ft_count_pipe(shell));
	else if (ft_is_subshell(sstoken))
		ft_subshell(shell, sstoken);
	else if (!ft_strcmp(*(shell->operator), "||"))
		ft_or(shell);
	else if (!ft_strcmp(*(shell->operator), "&&"))
		ft_and(shell);
	else if (!ft_strcmp(*(shell->operator), ">"))
		ft_right_redir(shell, ssoperator);
	else if (*(shell->operator) == NULL && sstoken != NULL)
		ft_exec_cmd(shell);
}

char	*getcmd(char *s, char **envp)
{
	int				start;
	char			*temp;
	static int		i = 0;
	static int		in_cmd_mode = 1;

	if (i == -2 || i == ft_strlen(s))
	{
		i = 0;
		in_cmd_mode = 1;
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
		else if (in_cmd_mode && !ft_isdigit(s[i]) && !ft_isalpha(s[i]) && ft_has(s[i], "|&><"))
		{
			in_cmd_mode = 0;
			return (ft_arg_check(getsub(s, start, i), envp));
		}
		else if (!in_cmd_mode && !ft_has(s[i], "|&><"))
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

int	ft_start(t_shell *shell)
{
	ft_creatematrix(shell);
	shell->operator_temp = shell->operator;
	shell->token_temp = shell->token;
	while(sstoken)
		ft_switch_op(shell);
	free(shell->cmd);
	free_matrix(shell->token_temp);
	free_matrix(shell->operator_temp);
	return (shell->fd_out);
}
