/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 02:49:57 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/08 18:48:223 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_right_redir(t_shell *shell ,char *op)
{
    int	i;

	i = 1;
	while (shell->token[i])
    {
        if (!ft_strncmp(op, ">>", 2))
            shell->redirec = open(shell->token[i], O_CREAT | O_APPEND | O_WRONLY, 0777);
        else if (!ft_strncmp(op, ">", 1))
            shell->redirec = open(shell->token[i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
        i++;
    }
    ft_exec_cmd(shell);
    while (!ft_strcmp(ssoperator, ">"))
    {
        shell->operator++;
        shell->token++;
    }
    if (sstoken)
        shell->token++;
    return (0);
}