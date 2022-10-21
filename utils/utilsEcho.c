/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsEcho.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:22:48 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/21 14:44:41 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*return_s(char *temp, char *last_quote, char *echo, char *copy)
{
	int	i;

	if (!ft_strcmp(echo, "echo $?"))
		return (echo);
	if (!(*last_quote))
	{
		i = 0;
		while (echo[i] && !ft_has(echo[i], "&|<>"))
			i++;
		return (getsub(echo, 0, i));
	}
	else
	{
		while (*temp && ft_strcmp(temp, last_quote))
			temp++;
	}
	temp++;
	*temp = '\0';
	free(copy);
	return (echo);
}

char	*ft_get_echo(char *s)
{
	char	*echo;
	char	*temp;
	char	*last_quote;
	char	*copy;

	copy = ft_strdup(s);
	echo = ft_strnstr(copy, "echo", ft_strlen(copy));
	if (!echo)
		return (NULL);
	temp = echo;
	last_quote = "";
	while (*temp)
	{
		if (*temp == 34)
		{
			last_quote = ft_strrchr(echo, 34);
			break ;
		}
		if (*temp == 39)
		{
			last_quote = ft_strrchr(echo, 39);
			break ;
		}
		if (ft_has(*temp, "&|<>"))
			break ;
		temp++;
	}
	return (return_s(temp, last_quote, echo, copy));
}