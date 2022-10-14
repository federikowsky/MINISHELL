/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:43:36 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/14 11:47:34 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_initializer(t_shell *shell)
{
	shell->filename = NULL;
	shell->operator = NULL;
	shell->token = NULL;
	shell->exitstatus = -1;
	shell->cmd = readline(PROMPT);
	shell->fd_in = 0;
	shell->fd_out = 1;
	shell->last_operator = "";
	shell->redirec = 0;
}

int	main_loop(t_shell *shell, char **envp)
{
	ft_envhandle(envp, shell);
	shell->home = ft_get_home(shell);
	// shell->fd_debug = open("FILE DEBUG", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (1)
	{
		sig_handling_set(1);
		ft_initializer(shell);
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
	main_loop(&shell, envp);
}
