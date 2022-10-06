/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:01:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/07 01:11:09 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_increase_shlvl(char ***mat)
{
	int 	i;
	char 	*value;
	
	i = 0;
	while(ft_strncmp((*mat)[i], "SHLVL", 5))
		i++;
	value = ft_itoa(ft_atoi(&(*mat)[i][6]) + 1);
	(*mat)[i] = ft_strjoin("SHLVL=", value);
	free(value);
}

char	**ft_mat_copy(char **mat)
{
	char	**res;
	int		i;
	
	res = (char **)malloc(sizeof(char *) * ft_find_lenght(mat));
	i = 0;
	while (mat[i])
	{
		res[i] = ft_strdup(mat[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_run_new_shell(t_shell *shell)
{
	char	**env_copy;
	int		status;
	pid_t 	pid;
	t_shell newshell;

	pid = fork();
	if (!pid)
	{
		env_copy = ft_mat_copy(shell->env);
		ft_increase_shlvl(&env_copy);
		main_loop(&newshell, env_copy);
		// exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		shell->exitstatus = WEXITSTATUS(status);
	}
}