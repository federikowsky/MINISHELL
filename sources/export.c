/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:07:56 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/26 19:20:21 by agenoves         ###   ########.fr       */
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
	static int	static_i = -1;
	char		*found;

	while (cmds[++static_i])
	{
		found = ft_strchr(cmds[static_i], '=');
		if (found != NULL)
			return (static_i);
	}
	static_i = -1;
	return (static_i);
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

char	**ft_split_export(char *str, int k, int i, int j)
{
	char	**cmds;

	cmds = NULL;
	cmds = ft_addelement(cmds, "");
	while (str[++i])
	{
		while (str[i + 1] && str[i] == 32 && str[i + 1] == 32)
			i++;
		if (str[i] == 34 || str[i] == 39)
		{
			if (str[i] == 34)
				j = ft_quoteparent(str + i, 34);
			else
				j = ft_quoteparent(str + i, 39);
			cmds[k] = ft_strjoin(cmds[k], ft_substr(str, i + 1, j - 1));
			cmds[k] = ft_strip(&cmds[k]);
			i += j;
			cmds = ft_addelement(cmds, "");
			k++;
		}
		else
			cmds[k] = ft_charjoin(cmds[k], str[i]);
	}
	cmds[k + 1] = 0;
	return (cmds);
}

int	ft_export(char *s, t_shell *shell)
{
	char	**cmds;
	char	*var;
	int		i;

	cmds = ft_split_export(s + 7, 0, -1, 0);
	i = ft_countvar(cmds);
	while (i != -1)
	{
		var = ft_check_export(cmds, i, shell);
		if (var != NULL)
			shell->env = ft_addenv(shell->env, var);
		else
			printf("Error export variable!\n");
		i = ft_countvar(cmds);
	}
	if (shell->exitstatus != 0)
		return (1);
	return (0);
}
