/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:37:59 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/21 12:12:18 by md-aless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_findquote(char *s, int start)
{
	int	found;

	found = -1;
	while (s[start])
	{
		if (ft_has(s[start], "\"\'"))
			found = start;
		start++;
	}
	return (found);
}

char	*ft_get_pwd(t_shell *shell)
{
	int		i;
	char	*pwd;

	i = 0;
	while (shell->env[i] != 0)
	{
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
			pwd = ft_split(shell->env[i], '=')[1];
		i++;
	}
	return (pwd);
}

int	ft_redir_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if ((cmd[i] == '>' && cmd[i + 1] == '>') || \
			(cmd[i] == '<' && cmd[i + 1] == '<'))
		{
			if ((cmd[i + 1] == '>' && cmd[i + 2] == '>') || \
			(cmd[i + 1] == '<' && cmd[i + 2] == '<'))
			{
				perror("Redir Check Problem: Minishell");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_find_redir(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->operator[i])
	{
		if (!ft_strcmp(shell->operator[i], ">") || \
				!ft_strcmp(shell->operator[i], ">>"))
			return (1);
		i++;
	}
	return (0);
}
