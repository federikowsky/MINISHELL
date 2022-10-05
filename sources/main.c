/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:36 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/05 15:02:51 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main_loop(t_shell *shell)
{
	while (1)
	{
		shell->operator = NULL;
		shell->token = NULL;
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


// ls | ps && echo ciao && grep c