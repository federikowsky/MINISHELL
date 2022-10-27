/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:15:07 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/27 11:10:09 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

char	*ft_arg_check(char *cmd, char **envp, int redi)
{
	char	**word;

	word = ft_split(cmd, ' ');
	if (ft_isbuiltin(word[0]) && access(word[0], F_OK) != 0 && \
			ft_pathfinder(word[0], envp) == NULL && !redi)
		printf("Minishell: command not found: %s\n", word[0]);
	return (cmd);
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

int	ft_quote_check_aux(char *cmd, int i)
{
	while (cmd[++i])
	{
		if (cmd[i] == 34)
		{
			if (ft_quoteparent(cmd + i, 34) != 0)
				i += ft_quoteparent(cmd + i, 34);
			else
				return (-1);
		}
		if (cmd[i] == 39)
		{
			if (ft_quoteparent(cmd + i, 39) != 0)
				i += ft_quoteparent(cmd + i, 39);
			else
				return (-1);
		}
	}
	return (0);
}

int	ft_quote_check(char *cmd)
{
	int	i;

	i = -1;
	if (ft_quote_check_aux(cmd, i) == -1)
	{
		perror("Quote Check Problem: Minishell");
		return (1);
	}
	return (0);
}
