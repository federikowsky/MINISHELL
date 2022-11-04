/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:02:41 by agenoves          #+#    #+#             */
/*   Updated: 2022/11/04 12:59:51 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_operator(char *cmd)
{
	if ((ft_bracket_check(cmd) || ft_quote_check(cmd) || ft_and_check(cmd) \
			|| ft_pipe_check(cmd) || ft_redir_check(cmd)))
		return (1);
	return (0);
}

int	ft_bracket_check(char *cmd)
{
	int	open;
	int	close;
	int	i;

	open = 0;
	close = 0;
	i = 0;
	while (cmd[i] != '\0' && i != -1)
	{
		i = ft_checkall(cmd, i);
		if (ft_has(cmd[i], "("))
			open += 1;
		if (ft_has(cmd[i], ")"))
			close += 1;
		i++;
	}
	if (open != close)
	{
		perror("Bracket check Problem: Minishell");
		return (1);
	}
	return (0);
}

int	ft_isbuiltin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0 \
		|| ft_strcmp(cmd, "exit") == 0 \
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0 \
		|| ft_strcmp(cmd, "unset") == 0 \
		|| ft_strcmp(cmd, "export") == 0)
		return (0);
	else
		return (1);
}

char	**ft_addelement(char **ss, char *cmd)
{
	char	**res;
	int		i;

	i = 0;
	if (ss == NULL)
		res = malloc(sizeof(char *) * 2);
	else
	{
		res = malloc(sizeof(char *) * (matln(ss) + 2));
		while (ss[i])
		{
			res[i] = ft_strdup(ss[i]);
			free(ss[i]);
			i++;
		}
		free(ss);
	}
	res[i++] = cmd;
	res[i] = NULL;
	return (res);
}
