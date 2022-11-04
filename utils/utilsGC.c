/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsGC.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:25:38 by fefilipp          #+#    #+#             */
/*   Updated: 2022/11/04 14:15:58 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

// garbage collector per le stringhe
char	*gc(t_shell *shell, char *s)
{
	shell->gc = ft_addelement(shell->gc, s);
	return (s);
}

// garbage collector per le matrici
static char	***gc2_aux(char ***sss, char **ss, int len)
{
	char	***res;
	int		i;

	i = 0;
	if (sss == NULL)
		res = malloc(sizeof(char ***) * 2);
	else
	{
		while (sss[len])
			len++;
		res = malloc(sizeof(char ***) * (len + 2));
		while (sss[i])
		{
			res[i] = ft_mat_copy(sss[i]);
			free_matrix(sss[i]);
			i++;
		}
	}
	res[i++] = ss;
	res[i] = NULL;
	return (res);
}

char	**gc2(t_shell *shell, char **ss)
{
	shell->gc2 = gc2_aux(shell->gc2, ss, 0);
	return (ss);
}