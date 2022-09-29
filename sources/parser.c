/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:16:40 by fefilipp          #+#    #+#             */
/*   Updated: 2022/09/29 16:06:38 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getCmd(char *s)
{
	int				start;
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
			return getSub(s, start + 1, i - 1);
		}
		else if (in_cmd_mode && !ft_isalpha(s[i]) && !ft_contained(s[i], " -.*"))
		{
			in_cmd_mode = 0;
			return getSub(s, start, i);
		}
		else if (!in_cmd_mode && !ft_contained(s[i], "|&"))
		{
			in_cmd_mode = 1;
			return getSub(s, start, i);
		}
		i++;
	}
	i = -2;
	return getSub(s, start, ft_strlen(s));
}
