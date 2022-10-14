/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:07:56 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/14 12:24:47 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Bisogna fare dei check per controllare la prima lettera della variabile da
 inserire con export che non deve essere né un numero né un carattere
 speciale. Dalla seconda lettera invece il numero lo accetta ma non il carattere
 speciale. */

int	ft_exist(char *s_env, char *s)
{
	char	*src;
	char	*to_check;

	src = ft_split(s, '=')[0];
	to_check = ft_split(s_env, '=')[0];
	if (ft_strncmp(src, to_check, ft_strlen(src)) == 0 && \
		ft_strlen(src) == ft_strlen(to_check))
		return (1);
	return (0);
}

char	**ft_addenv(char **matr, char *var)
{
	char	**newmatr;
	int		lenght;
	int		i;
	int		j;
	int		k;

	lenght = ft_mat_lenght(matr) + 1;
	newmatr = malloc(sizeof(char *) * (lenght));
	i = 0;
	j = 0;
	k = 0;
	while (matr[i])
	{
		if (var[k] == 92)
		{
			var[k] = 127;
			k++;
		}
		if (!ft_exist(matr[i], var))
			newmatr[j++] = ft_strdup(matr[i]);
		i++;
	}
	newmatr[j++] = ft_strdup(var);
	newmatr[j] = 0;
	return (newmatr);
}

int	ft_countvar(char **cmds)
{
	static int	static_i = 0;
	char		*found;

	while (cmds[++static_i])
	{
		found = ft_strchr(cmds[static_i], '=');
		if (found != NULL)
			return (static_i);
	}
	static_i = 0;
	return (0);
}

char	*ft_check_export(char **cmds, int i, t_shell *shell)
{
	char	**check;
	char	*err;

	check = ft_split(cmds[i], '=');
	err = check[0];
	if (!ft_isalpha(*check[0]))
	{
		printf("export: %s: not a valid identifier\n", err);
		shell->exitstatus = 1;
		return (0);
	}
	check[0]++;
	while (*check[0])
	{
		if (!(ft_isdigit(*check[0]) || ft_isalpha(*check[0])))
		{
			printf("export: %s: not a valid identifier\n", err);
			return (0);
		}
		check[0]++;
	}
	return (cmds[i]);
}

int	ft_export(char *s, t_shell *shell)
{
	char	*var;
	int		i;

	i = ft_countvar(ft_split(s, ' '));
	while (i)
	{
		var = ft_check_export(ft_split(s, ' '), i, shell);
		if (var != NULL)
			shell->env = ft_addenv(shell->env, var);
		else
			printf("Error export variable!\n");
		i = ft_countvar(ft_split(s, ' '));  
	}
	if (shell->exitstatus != 0)
		return (1);
	return (0);
		
}
