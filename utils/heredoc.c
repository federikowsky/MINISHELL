/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:38 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/27 15:23:23 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_shell *shell)
{
	char	*prompt;
	char	*input;
	char	*next_tok;

	next_tok = ft_get_cmd(shell);
	next_tok = ft_strip(&next_tok);
	prompt = ft_get_op(shell, 1);
	input = readline(prompt);
	while (ft_strcmp(input, next_tok))
		input = readline(prompt);
}
