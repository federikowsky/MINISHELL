/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:38 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 12:31:48 by md-aless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_shell *shell)
{
	char	*prompt;
	char	*input;
	char	*next_tok;

	next_tok = ft_get_cmd(shell->cmd, shell->env);
	next_tok = ft_strip(&next_tok);
	prompt = ft_get_op(shell, 1);
	input = readline(prompt);
	while (ft_strcmp(input, next_tok))
		input = readline(prompt);
}
