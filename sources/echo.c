/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:10:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/04 15:13:36 by agenoves         ###   ########.fr       */
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
 			printf("%s ", ss[i]);
 		i++;
 	}
 	if (!ss[1] || ft_strncmp(ss[1], "-n", 2) != 0)
 		printf("\n");
	else
		printf("\b");
 }
