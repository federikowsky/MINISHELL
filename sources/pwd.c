/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:11:22 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/04 13:24:29 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	*pwdpath;

	pwdpath = malloc(sizeof(char) * LEN_PATH);
	pwdpath = getcwd(pwdpath, LEN_PATH);
	printf("%s\n", pwdpath);
}
