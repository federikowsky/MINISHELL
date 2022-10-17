/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsEcho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:22:48 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/17 17:22:23 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_s(char *temp, char *last_quote, char *echo)
{
	if (!(*last_quote))
		return (NULL);
	// if (ft_quote_check(last_quote))
	// 	return (NULL);
	while (*temp && ft_strcmp(temp, last_quote))
		temp++;
	temp++;
	*temp = '\0';
	return echo;
}

char	*ft_get_echo(char *s)
{
	char	*echo;
	char	*temp;
	char	*last_quote;

	echo = ft_strnstr(s, "echo", ft_strlen(s));
	if (!echo)
		return (NULL);
	temp = echo;
	last_quote = "";
	while (*temp)
	{
		if (*temp == 34)
		{
			last_quote = ft_strrchr(echo, 34);
			break;
		}
		if (*temp == 39)
		{
			last_quote = ft_strrchr(echo, 39);
			break;
		}
		temp++;
	}
	return (return_s(temp, last_quote, echo));
}