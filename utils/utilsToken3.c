/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:02:41 by agenoves          #+#    #+#             */
/*   Updated: 2022/09/30 15:07:42 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check_operator(char *cmd)
{
	if (ft_bracket_check(cmd) || ft_quote_check(cmd) || ft_and_check(cmd) \
	|| ft_pipe_check(cmd))
		return(1);
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
	while (cmd[i] != '\0')
	{
		if (ft_contained(cmd[i], "("))
			open += 1;
		if (ft_contained(cmd[i], ")"))
			close += 1;
		i++;
	}
	if (open != close)
	{
		perror("Bracket check Problem: Minishell");
		return (1);
	}
	return (ft_bracket_aux(cmd));
}

int	ft_bracket_aux(char *cmd)
{
	int	is_op;
	int	i;

	is_op = 0;
	i = 0;
	while (cmd[i])
	{
		if (ft_contained(cmd[i], "|&\"'"))
			is_op = 1;
		if (ft_contained(cmd[i], "(") && !is_op)
		{
			perror("Minishell");
			return (1);
		}
		if (ft_isalpha(cmd[i]) && is_op)
			is_op = 0;
		i++;
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