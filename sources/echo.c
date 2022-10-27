/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:10:42 by fefilipp          #+#    #+#             */
/*   Updated: 2022/10/27 10:36:54 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_changeword(char *sentence, char *find, char *replace)
{
	int		len;
	char	*dest;
	char	*destptr;

	len = ft_strlen(sentence) - ft_strlen(find) + ft_strlen(replace) + 1;
	dest = malloc(len);
	destptr = dest;
	*dest = 0;
	while (*sentence)
	{
		if (!ft_strncmp(sentence, find, ft_strlen(find)))
		{
			strcat (destptr, replace);
			sentence += ft_strlen(find);
			destptr += ft_strlen(replace);
		}
		else
		{
			*destptr = *sentence;
			destptr++;
			sentence++;
		}
	}
	*destptr = 0;
	return (dest);
}

char	*ft_env_var(char *cmd, t_shell *shell)
{
	int		i;
	int		len_key;
	char	*key;
	char	*value;

	i = 0;
	len_key = 1;
	key = ft_strchr(ft_strdup(cmd), '$');
	if (!key)
		return (cmd);
	while (ft_isalpha(key[len_key]))
		len_key++;
	key[len_key] = '\0';
	while (shell->env[i] && \
		ft_strncmp(key + 1, shell->env[i], ft_strlen(key + 1)) != 0)
		i++;
	if (!shell->env[i])
		return (ft_changeword(cmd, key, ""));
	value = ft_split(shell->env[i], '=')[1];
	return (ft_changeword(cmd, key, value));
}

char	*ft_echo_quote(char	*str, char *echo, char *temp, t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i + 1] && str[i] == 32 && str[i + 1] == 32)
			i++;
		if (str[i] == 36)
		{
			j = i;
			while (str[i] && str[i] != ' ')
				i++;
			temp = ft_substr(str, j, i - j - 1);
			echo = ft_strjoin(echo, ft_env_var(temp, shell));
		}
		if (str[i] == 34 || str[i] == 39)
		{
			if (str[i] == 34)
				j = ft_quoteparent(str + i, 34);
			else
				j = ft_quoteparent(str + i, 39);
			temp = ft_substr(str, i + 1, j - 1);
			echo = ft_strjoin(echo, ft_env_var(temp, shell));
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
	char	*x;

	str = NULL;
	if (ft_strcmp(*(shell->tok), "echo $?") == 0)
	{
		printf("%d\n", shell->prev_exitstatus);
		shell->prev_exitstatus = 0;
		return ;
	}
	ss = ft_split(*(shell->tok), ' ');
	if (ss[1] && !ft_strncmp(ss[1], "-n", 2))
	{
		str = ft_substr(*(shell->tok), 7, ft_strlen(*(shell->tok)));
		x = ft_echo_quote(str, "", NULL, shell);
		printf("%s", ft_strip(&x));
	}
	else
	{
		str = ft_substr(*(shell->tok), 5, ft_strlen(*(shell->tok)));
		printf("%s\n", ft_echo_quote(str, "", NULL, shell));
	}
}
