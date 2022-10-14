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
    if (!ft_strncmp(op, ">>", 2))
    {
        sstoken++;
        shell->filename = sstoken;  
        shell->redirec = open(shell->filename, O_CREAT | O_APPEND | O_WRONLY, 0777);
        sstoken--;
    }
    else if (!ft_strncmp(op, ">", 1))
    {
        sstoken++;
        shell->filename = sstoken;
        shell->redirec = open(shell->filename, O_CREAT | O_TRUNC | O_WRONLY, 0777);
        sstoken--;
    }
    ft_exec_cmd(shell);
    if (sstoken)
        shell->token++;
    return (0);
}