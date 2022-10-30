/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:58:58 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/28 14:13:48 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define DIRECTORY  4
#define FILE       8

int	ft_wild_match(char *src, char *to_check)
{
	if (!*src)
		return (1);
	if (*src == '*')
		return (ft_wild_match(src + 1, to_check));
	if (*src == *to_check)
		return (ft_wild_match(src + 1, to_check + 1));
	if (ft_has(*src, to_check))
		return (ft_wild_match(src, to_check + 1));
	else
		return (0);
}

void	ft_wild_file(char *s, t_shell *shell, int *exist)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*dir;

	dir = ft_ret_dir(&s);
	folder = opendir(dir);
	entry = readdir(folder);
	if (ft_strcmp(dir, "."))
		dir = ft_strjoin(dir, "/");
	else
		dir = "";
	while (entry)
	{
		if (ft_isalpha(entry->d_name[0]) && entry->d_type == FILE && \
				ft_wild_match(s, entry->d_name))
		{
			if (s[0] == entry->d_name[0] || !ft_strncmp(s, "*", 1))
			{
				ft_exec_cmd_aux(shell, ft_wild_cmd(shell, ft_strjoin(dir, entry->d_name)));
				*exist = 1;
			}
		}
		entry = readdir(folder);
	}
	closedir(folder);
}

void	ft_wild_dir(char *s, t_shell *shell, int num_arg, int *exist)
{
	DIR				*folder;
	struct dirent	*entry;
	char			*dir;

	dir = ft_ret_dir(&s);
	folder = opendir(dir);
	entry = readdir(folder);
	if (ft_strcmp(dir, "."))
		dir = ft_strjoin(dir, "/");
	else
		dir = "";
	while (entry)
	{
		if (ft_isalpha(entry->d_name[0]) && entry->d_type == DIRECTORY && \
			ft_wild_match(s, entry->d_name) && 							   \
			(s[0] == entry->d_name[0] || !ft_strncmp(s, "*", 1)))
		{
				printf("\n");
				if (num_arg > 2 || *s == '*')
					printf("%s:\n", ft_strjoin(dir, entry->d_name));
				ft_exec_cmd_aux(shell, ft_wild_cmd(shell, ft_strjoin(dir, entry->d_name)));
				*exist = 1;
		}
		entry = readdir(folder);
	}
	closedir(folder);
}

void	ft_wild(t_shell *shell)
{
	char			**arg;
	int				i;
	int				exist;

	i = 0;
	arg = ft_split(*(shell->tok), ' ');
	while (arg[++i])
	{
		if (arg[i][0] == '-')
			continue ;
		exist = 0;
		ft_wild_file(arg[i], shell, &exist);
		ft_wild_dir(arg[i], shell, matln(arg), &exist);
		if (!exist)
			printf("%s: %s: No such file or directory\n", arg[0], arg[i]);
	}
	shell->last_operator = *(shell->op);
	shell->tok++;
	shell->op++;
}
