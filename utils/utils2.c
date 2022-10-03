/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:01:28 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/03 23:41:31 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin(char *token, t_shell *shell)
{
	char	**cmd;

	cmd = ft_split(token, ' ');
	(void) shell;
	if (ft_strcmp(cmd[0], "pwd") == 0)
		printf("il comando da eseguire é: %s\n", token);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		printf("il comando da eseguire é: %s\n", token);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		printf("il comando da eseguire é: %s\n", token);
	else if (ft_strcmp(cmd[0], "env") == 0)
		printf("il comando da eseguire é: %s\n", token);	
	else if (ft_strcmp(cmd[0], "echo") == 0)
		printf("il comando da eseguire é: %s\n", token);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		printf("il comando da eseguire é: %s\n", token);
	else if (ft_strcmp(cmd[0], "export") == 0)
		printf("il comando da eseguire é: %s\n", token);
	else
	{
		printf("minishell: %s: command not found\n", token);
		return (1);
	}
	return (0);
}

void	ft_print_mat(char **ss)
{
	int	i;

	i = 0;
	while (ss[i])
	{
		printf("%s\n", ss[i]);
		i++;	
	}
}
