/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:10:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/25 19:25:10 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*ft_dollar_echo(char *cmd, t_shell *shell)
// {
// 	char	**mypaths;
// 	int		i;

// 	i = 0;
// 	while (shell->env[i] && ft_strncmp(cmd, shell->env[i], 4) != 0)
// 		i++;
// 	if (!shell->env[i])
// 		return (NULL);
// 	mypaths = ft_split(shell->env[i], '=');
// 	return (mypaths[1]);
// }

int	ft_quoteparent(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_echo_quote(char	*str, t_shell *shell)
{
	int		i;
	int		j;
	char	*echo;
	char	*temp;

	i = 0;
	j = 0;
	(void) shell;
	echo = "";
	while (str[i])
	{
		while (str[i + 1] && str[i + 1] == 32)
			i++;
		if (str[i] == 34)
		{
			j = ft_quoteparent(str + i, '\"');
			temp = ft_substr(str, i + 1, j - 1);
			echo = ft_strjoin(echo, temp);
			free(temp);
			i += j;
		}
		else if (str[i] == 39)
		{
			j = ft_quoteparent(str + i, '\'');
			temp = ft_substr(str, i + 1, j - 1);
			echo = ft_strjoin(echo, temp);
			free(temp);
			i += j;
		}
		else
			echo = ft_charjoin(echo, str[i]);
		i++;
	}
	if (echo)
		return (echo);
	else
		return (str);
}

char	*ft_get_echo2(char *token)
{
	char	*cmd;
	char	*temp;
	char	*copy;

	copy = ft_strdup(token);
	cmd = ft_strnstr(copy, "echo", ft_strlen(copy));
	if (!cmd)
		return (" ");
	temp = cmd + 5;
	while (*temp)
	{
		while (*temp == 32)
			temp++;
		if (*temp == 34)
			temp = ft_strchr(temp + 1, 34);
		if (*temp == 39)
			temp = ft_strchr(temp + 1, 39);
		if (ft_has(*temp, "|&<>"))
			break ;
		temp++;
	}
	free(copy);
	return (ft_substr(cmd, 0, temp - cmd));
}

void	ft_echo(t_shell *shell)
{
	char	**ss;
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	if (ft_strcmp(sstoken, "echo $?") == 0)
	{
		printf("%d\n", shell->prev_exitstatus);
		shell->prev_exitstatus = 0;
		return ;
	}
	ss = ft_split(sstoken, ' ');
	if (!ft_strncmp(ss[1], "-n", 2))
	{
		str = ft_substr(sstoken, 7, ft_strlen(sstoken));
		printf("%s", ft_echo_quote(str, shell));
	}
	else
	{
		str = ft_substr(sstoken, 5, ft_strlen(sstoken));
		printf("%s\n", ft_echo_quote(str, shell));
	}
}
