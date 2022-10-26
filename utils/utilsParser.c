/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsParser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 00:24:09 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 19:35:55 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_quote(char *str, char c)
{
	char	*temp;
	int		len;

	temp = str;
	while (*temp)
	{
		len = ft_strlen(temp);
		if (*temp == c)
			ft_memmove(temp, temp + 1, len);
		temp++;
	}
}

char	*ft_check_quote(char **token)
{
	int	i;

	i = 0;
	if (!(*token))
		return (NULL);
	if (!ft_strncmp(*(token), "echo", 4))
		return (*token);
	if (!ft_strncmp(*(token), "export", 6))
		return (*token);
	while ((*token)[i])
	{
		if ((*token)[i] == 34)
		{
			ft_remove_quote(*token, 34);
			break ;
		}
		if ((*token)[i] == 39)
		{
			ft_remove_quote(*token, 39);
			break ;
		}	
		i++;
	}
	return (*token);
}

char	*ft_get_op(t_shell *shell, int heredoc)
{
	int		i;
	char	*res;
	char	*curr_op;

	i = 0;
	curr_op = "";
	res = "";
	while (shell->op && shell->op[i])
	{
		if (i != 0 && !ft_strcmp(shell->op[i], "|"))
			curr_op = "pipe ";
		else if (!ft_strcmp(shell->op[i], "&&"))
			curr_op = "cmdand ";
		else if (!ft_strcmp(shell->op[i], "||"))
			curr_op = "cmdor ";
		res = ft_strjoin(res, curr_op);
		i++;
	}
	if (heredoc)
		res = ft_strjoin(res, "heredoc ");
	res = ft_strjoin(res, "\b> ");
	return (res);
}

void	ft_append_cmd(t_shell *shell)
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
		if (in_cmd_mode && !ft_strncmp(s + i, "echo", 4) && ft_get_echo2(s + i) != NULL)
		{
			int curr_ind = i;
			in_cmd_mode = 0;
			i += ft_strlen(ft_get_echo(s + i));
			return (ft_arg_check(ft_get_echo2(s + curr_ind), envp, is_red));
		}
		if (in_cmd_mode && ft_has(s[i], "\"\'"))
		{
			in_cmd_mode = 0;
			is_red = 0;
			i = findparenth(s, start, "\"\'") + 1;
			return (ft_arg_check(getsub(s, start, i), envp, is_red));
		}
		if (in_cmd_mode && ft_has(s[i], "("))
		{
			in_cmd_mode = 0;
			is_red = 0;
			i = findparenth(s, start, ")") + 1;
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
