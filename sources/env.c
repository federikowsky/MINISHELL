/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:10:33 by agenoves          #+#    #+#             */
/*   Updated: 2022/09/23 16:49:32 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_envhandle(char **envp, t_shell *shell)
{
	int		i;

	shell->env = malloc(sizeof(char *) * (ft_find_lenght(envp) + 1));
	i = -1;
	if (!shell->env)
		exit(printf("Error allocating env\n"));
	while (envp[++i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env)
			exit(printf("Error setting env\n"));
	}
	shell->env[i] = 0;
}

void	ft_printenv(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->env[++i] != 0)
		printf("%s\n", shell->env[i]);
}
