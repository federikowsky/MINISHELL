/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/21 15:30:48 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_switch_op(t_shell *shell)
{
	if (ft_strcmp(sstoken, "./minishell") == 0)
		ft_run_new_shell(shell);
	else if (!ft_strcmp(*(shell->operator), "|"))
		ft_exec_pipe(shell, ft_count_pipe(shell));
	else if (ft_is_subshell(sstoken))
		ft_subshell(shell, sstoken);
	else if (!ft_strcmp(*(shell->operator), "||"))
		ft_or(shell);
	else if (!ft_strcmp(*(shell->operator), "&&"))
		ft_and(shell);
	else if (!ft_strcmp(*(shell->operator), ">") || \
		!ft_strcmp(*(shell->operator), ">>"))
		ft_right_redir(shell);
	else if (!ft_strcmp(*(shell->operator), "<"))
		ft_left_redir(shell);
	else if (*(shell->operator) == NULL && sstoken != NULL)
		ft_exec_cmd(shell);
	if (!ft_strcmp(*(shell->operator), ">") || \
		!ft_strcmp(*(shell->operator), ">>"))
		ft_skip_redirection(shell);
}

int	ft_start(t_shell *shell)
{
	ft_creatematrix(shell);
	shell->operator_temp = shell->operator;
	shell->token_temp = shell->token;
	ft_redirection(shell);
	while (sstoken)
		ft_switch_op(shell);
	free(shell->cmd);
	free_matrix(shell->token_temp);
	free_matrix(shell->operator_temp);
	return (shell->exitstatus);
}
