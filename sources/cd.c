/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:20:38 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/05 12:14:54 by md-aless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_cd(t_shell *shell)
{
	int	i;

	i = 2;
	while ((sstoken)[i] != '\0')
	{
		if ((sstoken)[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_home(t_shell *shell)
{
	int		i;
	char	*home;

	i = 0;
	while (shell->env[i] != 0)
	{
		if (!ft_strncmp(shell->env[i], "HOME=", 5))
			home = ft_split(shell->env[i], '=')[1];
		i++;
	}
	return (home);
}

void	ft_update_env(t_shell *shell, char *pwd)
{
	int		i;
	char	*newpwd;

	i = 0;
	newpwd = malloc(sizeof(char) * LEN_PATH);
	while (shell->env[i] != 0)
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
			shell->env[i] = ft_strjoin("OLDPWD=", pwd);
		else if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			newpwd = getcwd(newpwd, LEN_PATH);
			shell->env[i] = ft_strjoin("PWD=", newpwd);
		}
		i++;
	}
}

void	ft_cd(t_shell *shell)
{
	char	*pathdest;
	char	*word;
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, LEN_PATH);
	pathdest = malloc(sizeof(char) * LEN_PATH);
	word = ft_substr(sstoken, 3, ft_strlen(sstoken));
	pathdest = word;
	if (!ft_check_cd(shell))
	{
		chdir(shell->home);
		ft_update_env(shell, oldpwd);
		free(pathdest);
	}
	else if (chdir(pathdest) == 0)
		ft_update_env(shell, oldpwd);
	else
	{
		printf("%s%s\n", "cd: no such file or directory: ", pathdest);
		free(pathdest);
	}
}
