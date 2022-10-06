/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:11:22 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/06 16:34:00 by fefilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(void)
{
	char	*pwdpath;

	pwdpath = malloc(sizeof(char) * LEN_PATH);
	pwdpath = getcwd(pwdpath, LEN_PATH);
	printf("%s\n", pwdpath);
	return (pwdpath);
}
