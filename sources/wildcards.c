/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:58:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/27 10:32:11 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define DIRECTORY  4
#define FILE       8

void	ft_wild(t_shell *shell)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*arg;

	arg = ft_split(*(shell->tok), ' ')[1];
	if (!arg)
		folder = opendir(".");
	else
		folder = opendir(arg);
	entry = readdir(folder);
	while (entry)
	{
		if (ft_isalpha(entry->d_name[0]))
		{
			printf("%s\n", entry->d_name);
			ft_exec_cmd_aux(shell, entry->d_name);
			entry = readdir(folder);
		}
	}
	closedir(folder);
}
