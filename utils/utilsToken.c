/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsToken.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:46:53 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/21 14:57:52 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strip(char **s)
{
	if (*s == NULL)
		return (NULL);
	while (**s == ' ')
		(*s)++;
	while ((*s)[ft_strlen(*s) - 1] == ' ')
		(*s)[ft_strlen(*s) - 1] = '\0';
	return (*s);
}

int	ft_has(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	findparenth(const char *s, int start, char *c)
{
	int	found;

	found = -1;
	while (s[start])
	{
		if (ft_has(s[start], c))
			found = start;
		start++;
	}
	return (found);
}

char	*getsub(const char *s, int start, int end)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (end - start));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

int	ft_get_cmd_aux(char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == ')')
		(*i)++;
	return (*i);
}
