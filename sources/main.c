/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:36 by fefilipp          #+#    #+#             */
/*   Updated: 2022/09/29 16:36:58 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_tree *tree = NULL;
	char *s = "";
	if (ft_check_operator(argv[1]))
    {
        printf("Syntax Error\n");
        return (1);
    }
	while (s != NULL)
	{
		s = getCmd(argv[1]);
		if (s != NULL)
			printf("%s\n", ft_strip(&s));
		else
			break;
	}
	return 0;
}
