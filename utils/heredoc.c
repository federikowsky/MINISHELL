/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:38 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/16 15:10:54 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_heredoc(t_shell *shell)
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