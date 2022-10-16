/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsParser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 00:24:09 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/16 15:12:16 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_op(t_shell *shell, int heredoc)
{
	int		i;
	char	*res;
	char	*curr_op;

	i = 0;
	curr_op = "";
	res = "";
	while(shell->operator[i])
	{
		if (i != 0 && !ft_strcmp(shell->operator[i], "|"))
			curr_op = "pipe ";
		else if (!ft_strcmp(shell->operator[i], "&&"))
			curr_op = "cmdand ";
		else if (!ft_strcmp(shell->operator[i], "||"))
			curr_op = "cmdor ";
		res = ft_strjoin(res, curr_op);
		i++;
	}
	if (heredoc)
		res = ft_strjoin(res, "heredoc ");
	res = ft_strjoin(res, "\b> ");
	return (res);
}

void ft_append_cmd(t_shell *shell)
{
	char	*prompt;
	
	prompt = ft_get_op(shell, 0);
	shell->cmd = readline(prompt);
	while (*(shell->cmd) == '\0')
		shell->cmd = readline(prompt);
	ft_creatematrix(shell);
	
}

char	*ft_get_cmd(char *s, char **envp)
{
	int				start;
	char			*temp;
	static int		i = 0;
	static int		in_cmd_mode = 1;
	static int		is_red = 0;

	if (i == -2 || i == ft_strlen(s))
	{
		i = 0;
		in_cmd_mode = 1;
		return (NULL);
	}
	start = ft_get_cmd_aux(s, &i);
	while (s[i])
	{
		if (ft_has(s[i], "<>"))
			is_red = 1;
		if (in_cmd_mode && ft_has(s[i], "\"\'"))
		{
			in_cmd_mode = 0;
			is_red = 0;
			i = ft_findquote(s, start) + 1;
			return (ft_arg_check(getsub(s, start, i), envp, is_red));
		}
		if (in_cmd_mode && ft_has(s[i], "("))
		{
			in_cmd_mode = 0;
			is_red = 0;
			i = findparenth(s, start) + 1;
			return (ft_arg_check(getsub(s, start + 1, i - 1), envp, is_red));
		}
		else if (in_cmd_mode && !ft_isdigit(s[i]) && !ft_isalpha(s[i]) && ft_has(s[i], "|&><"))
		{
			in_cmd_mode = 0;
			return (ft_arg_check(getsub(s, start, i), envp, is_red));
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
		return (ft_arg_check(temp, envp, is_red));
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
		if (ft_strcmp(operator, "<<"))
		{
			token = ft_get_cmd(shell->cmd, shell->env);
			token = ft_strip(&token);
			shell->token = ft_addelement(shell->token, token);
		}
		if (!token)
			break;
		operator = ft_get_cmd(shell->cmd, shell->env);
		operator = ft_strip(&operator);
		if (!ft_strcmp(operator, "<<"))
		{
			ft_heredoc(shell);
		}
		else
			shell->operator = ft_addelement(shell->operator, operator);
	}
	if (ft_mat_lenght(shell->token) == ft_mat_lenght(shell->operator))
		ft_append_cmd(shell);
}