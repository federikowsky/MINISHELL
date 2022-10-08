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

    if ((shell->last_operator)[0] =='\0')
        ft_exec_cmd(shell);
    while (ft_has((*(shell->operator + 1))[0], ">"))
    {
        if (!ft_strncmp(op, ">>", 2))
            shell->redirec = open(sstoken, O_CREAT | O_APPEND | O_WRONLY, 0777);
        else if (!ft_strncmp(op, ">", 1))
            shell->redirec = open(sstoken, O_CREAT | O_TRUNC | O_WRONLY, 0777);
        shell->token++;
        shell->operator++;
    }
    if (sstoken)
        shell->token++;
    return (0);
}