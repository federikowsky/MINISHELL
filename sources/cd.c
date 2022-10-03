/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:41:50 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/03 14:42:12 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
