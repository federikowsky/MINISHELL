/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsParser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:33:06 by md-aless          #+#    #+#             */
/*   Updated: 2022/10/26 12:33:44 by md-aless         ###   ########.fr       */
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
			shell->token = ft_addelement(shell->token, token);
		}
		if (!token)
			break ;
		operator = ft_get_cmd(shell->cmd, shell->env);
		operator = ft_strip(&operator);
		if (!ft_strcmp(operator, "<<"))
			ft_heredoc(shell);
		else
			shell->operator = ft_addelement(shell->operator, operator);
	}
	if (shell->token && shell->operator && \
			ft_mat_lenght(shell->token) == ft_mat_lenght(shell->operator))
		ft_append_cmd(shell);
}