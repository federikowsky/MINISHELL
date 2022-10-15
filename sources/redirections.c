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

void ft_redir_exec(t_shell *shell)
{
	int		fileout;

	fileout = dup(STDOUT_FILENO);
    dup2(shell->redirec, STDOUT_FILENO);
	close(shell->redirec);
	ft_right_redir(shell);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
}

void ft_redirection(t_shell *shell)
{
    int	i;
    int j;

	i = 1;
    j = 0;
	while (shell->token[i])
    {
        if (!ft_strncmp(shell->operator[j], ">>", 2))
            shell->redirec = open(shell->token[i], O_CREAT | O_APPEND | O_WRONLY, 0777);
        else if (!ft_strncmp(shell->operator[j], ">", 1))
            shell->redirec = open(shell->token[i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
        i++;
        j++;
    } 
}

int ft_right_redir(t_shell *shell)
{
    ft_redirection(shell);
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

void ft_skip_redirection(t_shell *shell)
{
    while (!ft_strcmp(ssoperator, ">"))
    {
        shell->operator++;
        shell->token++;
    }
    if (sstoken)
        shell->token++;
}