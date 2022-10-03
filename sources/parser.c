/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/09/30 16:22:46 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getCmd(char *s, char **envp)
{
	int				start;
	char			*temp;
	static int		i = 0;
	static int		in_cmd_mode = 1;
	if (i == -2)
		return NULL;
	start = getCmd_aux(s, &i);
	while (s[i])
	{
		if (in_cmd_mode && ft_contained(s[i], "(\"'"))
		{
			in_cmd_mode = 0;
			i = findParenth(s, start) + 1;
			return(ft_arg_check(getSub(s, start + 1, i - 1), envp));
		}
		else if (in_cmd_mode && !ft_isalpha(s[i]) && !ft_contained(s[i], " -.*"))
		{
			in_cmd_mode = 0;
			getSub(s, start, i);
			return(ft_arg_check(getSub(s, start, i), envp));
		}
		else if (!in_cmd_mode && !ft_contained(s[i], "|&"))
		{
			in_cmd_mode = 1;
			return(getSub(s, start, i));
		}
		i++;
	}
	i = -2;
	temp = getSub(s, start, ft_strlen(s));
	if (*temp)
		return(ft_arg_check(temp, envp));
	return (NULL);
}
