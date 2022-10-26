/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsParser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:33:06 by md-aless          #+#    #+#             */
/*   Updated: 2022/10/26 19:37:36 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_creatematrix(t_shell *shell)
{
	char	*token;
	char	*operator;

	token = " ";
	operator = " ";
	while (token != NULL && operator != NULL)
	{
		if (ft_strcmp(operator, "<<"))
		{
			token = ft_get_cmd(shell->cmd, shell->env);
			token = ft_strip(&token);
			token = ft_check_quote(&token);
			shell->tok = ft_addelement(shell->tok, token);
		}
		if (!token)
			break ;
		operator = ft_get_cmd(shell->cmd, shell->env);
		operator = ft_strip(&operator);
		if (!ft_strcmp(operator, "<<"))
			ft_heredoc(shell);
		else
			shell->op = ft_addelement(shell->op, operator);
	}
	if (shell->tok && shell->op && \
		ft_mat_lenght(shell->tok) == ft_mat_lenght(shell->op))
		ft_append_cmd(shell);
}
