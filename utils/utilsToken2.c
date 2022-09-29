/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:15:07 by fefilipp          #+#    #+#             */
/*   Updated: 2022/09/29 16:36:09 by fefilipp         ###   ########.fr       */
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
	return (0);
}

int	ft_quote_check(char *cmd)
{
	int	quote;
	int	doublequote;
	int	i;
	
	quote = 0;
	doublequote = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (ft_contained(cmd[i], "'"))
			quote += 1;
		if (ft_contained(cmd[i], "\""))
			doublequote += 1;
		i++;
	}
	if (quote % 2 != 0 || doublequote % 2 != 0)
	{
		perror("Quote check Problem: Minishell");
		return (1);
	}
	return (0);
}

int	ft_pipe_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' && cmd[i + 1] == '|')
		{
			if (cmd[i + 1] == '|' && cmd[i + 2] == '|')
			{
				perror("Pipe Check Problem: Minishell");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_and_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '&' && cmd[i + 1] != '&' && cmd[i - 1] != '&')
		{
			
			perror("And Check Problem: Minishell");
			return (1);
		}
		else if (cmd[i] == '&' && cmd[i + 1] == '&')
		{
			if (cmd[i + 1] == '&' && cmd[i + 2] == '&')
			{
				perror("And Check Problem: Minishell");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
