/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/26 19:37:39 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_switch_op(t_shell *shell)
{
	if (ft_strcmp(*(shell->tok), "./minishell") == 0)
		ft_run_new_shell(shell);
	else if (!ft_strcmp(*(shell->op), "|"))
		ft_exec_pipe(shell, ft_count_pipe(shell));
	else if (ft_is_subshell(*(shell->tok)))
		ft_subshell(shell, *(shell->tok));
	else if (!ft_strcmp(*(shell->op), "||"))
		ft_or(shell);
	else if (!ft_strcmp(*(shell->op), "&&"))
		ft_and(shell);
	else if (!ft_strcmp(*(shell->op), ">") || \
		!ft_strcmp(*(shell->op), ">>"))
		ft_right_redir(shell);
	else if (!ft_strcmp(*(shell->op), "<"))
		ft_left_redir(shell);
	else if (*(shell->op) == NULL && *(shell->tok) != NULL)
		ft_exec_cmd(shell);
	if (!ft_strcmp(*(shell->op), ">") || \
		!ft_strcmp(*(shell->op), ">>"))
		ft_skip_redirection(shell);
}

int	ft_start(t_shell *shell)
{
	ft_creatematrix(shell);
	shell->op_temp = shell->op;
	shell->tok_temp = shell->tok;
	ft_redirection(shell);
	while (*(shell->tok))
		ft_switch_op(shell);
	free(shell->cmd);
	free_matrix(shell->tok_temp);
	free_matrix(shell->op_temp);
	return (shell->exitstatus);
}
