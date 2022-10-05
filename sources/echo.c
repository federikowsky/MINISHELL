/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:10:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/05 16:23:04 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_shell *shell)
 {
 	char	**ss;
 	int		i;

 	ss = ft_split(sstoken, ' ');
 	i = 1;
 	while (ss[i])
 	{
 		if (ft_strncmp(ss[i], "-n", 2) != 0)
 			printf("%s", ss[i]);
		if (ss[i + 1] != NULL)
			printf(" ");
 		i++;
 	}
 	if (!ss[1] || ft_strncmp(ss[1], "-n", 2) != 0)
 		printf("\n");
	else
		printf("\b");
 }
