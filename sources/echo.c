/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:10:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/19 03:01:17 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 34 "
// 39 '

char	*ft_get_echo2(char *token)
{
	char	*cmd;
	char	*temp;
	
	cmd = ft_strnstr(token, "echo", ft_strlen(token));
	temp = cmd + 5;
	while(*temp)
	{
		while(*temp == 32)
			temp++;
		if (ft_has(*temp, "|&<>"))
			break;
		if (*temp == 34)
		{
			ft_memmove(temp, temp + 1, ft_strlen(temp));
			temp = ft_strchr(temp + 1, 34);
			if (!temp)
			{
				perror("Error: unclosed quote");
				return (NULL);
			}
			ft_memmove(temp, temp + 1, ft_strlen(temp));
		}
		if (*temp == 39)
		{
			ft_memmove(temp, temp + 1, ft_strlen(temp));
			temp = ft_strchr(temp + 1, 39);
			if (!temp)
			{
				perror("Error: unclosed quote");
				return (NULL);
			}
			ft_memmove(temp, temp + 1, ft_strlen(temp));
		}
		temp++;
	}
	return (ft_substr(cmd, 0, temp - cmd));
}

void	ft_echo(t_shell *shell)
 {
 	char	**ss;
 	int		i;

	if (ft_strcmp(sstoken, "echo $?") == 0)
	{
		printf("%d\n", shell->prev_exitstatus);
		shell->prev_exitstatus = 0;
		return ;
	}
 	ss = ft_split(sstoken, ' ');
 	i = 1;
 	while (ss[i])
 	{
 		if (ft_strncmp(ss[i], "-n", 2) != 0)
 			printf("%s", ss[i]);
		if (ss[i + 1] != NULL)
			printf(" ");
 		i++;
 	}
 	if (!ss[1] || ft_strncmp(ss[1], "-n", 2) != 0)
 		printf("\n");
	else
		printf("\b");
}
