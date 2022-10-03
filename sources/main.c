/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:36 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/03 16:40:47 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main_loop(t_shell *shell)
{
	while (1)
	{
		shell->cmd = readline(PROMPT);
		if (!shell->cmd)
			return (write (1, "\n", 1));
		if (shell->cmd)
			add_history(shell->cmd);
		if (ft_check_operator(shell->cmd))
			printf("Waiting for new command...\n");
		else
			ft_start(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	(void) envp;
	ft_envhandle(envp, &shell);
	shell.home = ft_get_home(&shell);
	sig_handling_set(1);
	main_loop(&shell);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char *s = "";
// 	if (ft_check_operator(argv[1]))
//     {
//         printf("Syntax Error\n");
//         return (1);
//     }
// 	while (s != NULL)
// 	{
// 		s = getcmd(argv[1], envp);
// 		if (s != NULL)
// 			printf("%s\n", ft_strip(&s));
// 		else
// 			break;
// 	}
// 	return 0;
// }
