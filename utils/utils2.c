/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 19:01:28 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/03 19:15:01 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_builtin(char *cmd, t_shell *shell)
{
	(void) shell;
	if (ft_strcmp(cmd, "pwd") == 0)
		printf("il comando da eseguire é: %s\n", cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		printf("il comando da eseguire é: %s\n", cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		printf("il comando da eseguire é: %s\n", cmd);
	else if (ft_strcmp(cmd, "env") == 0)
		printf("il comando da eseguire é: %s\n", cmd);	
	else if (ft_strcmp(cmd, "echo") == 0)
		printf("il comando da eseguire é: %s\n", cmd);
	else if (ft_strcmp(cmd, "unset") == 0)
		printf("il comando da eseguire é: %s\n", cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		printf("il comando da eseguire é: %s\n", cmd);
	else
	{
		printf("minishell: %s: command not found\n", cmd);
		return (0);
	}
	return (1);
}
