/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsWildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 02:32:16 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/28 13:33:04 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_ret_dir(char **dir)
{
	char	*res;
	char	*temp;
	char	**sub_dir;
	int		i;
	
	res = "";
	i = 0;
	if (!ft_is_dir(*dir))
		return (*dir);
	sub_dir = ft_split(*dir, '/');
	temp = ft_strdup(".");
	res = ft_strjoin(res, sub_dir[i++]);
	while (sub_dir[i] && !ft_is_dir(res))
	{
		free(temp);
		temp = ft_strdup(res);
		res = ft_strjoin(res, "/");
		res = ft_strjoin(res, sub_dir[i++]);
	}
	*dir = sub_dir[--i];
	return (temp);
}

int ft_is_dir(const char* fileName)
{
    // struct stat path;

    // stat(fileName, &path);

    // return S_ISREG(path.st_mode);
	DIR* dir = opendir(fileName);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	else
		return (1);
}

char	*ft_wild_cmd(t_shell *shell, char *arg)
{
	char	*temp;
	char	**splitted;

	temp = "";
	splitted = ft_split(*(shell->tok), ' ');
	temp = ft_strjoin(temp, splitted[0]);
	if (splitted[1][0] == '-')
	{
		temp = ft_strjoin(temp, " ");
		temp = ft_strjoin(temp, splitted[1]);
	}
	temp = ft_strjoin(temp, " ");
	temp = ft_strjoin(temp, arg);
	return (temp);
}