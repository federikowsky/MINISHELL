/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agenoves <agenoves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:23 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/03 15:17:00 by agenoves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define PROMPT "\e[1;3;37mmi\e[1;3;36mni\e[1;3;37msh\e[1;3;36mel\e[1;3;37ml$ "
# define LEN_PATH 4096

typedef struct s_shell
{
	char	**env;
	char	*cmd;
	char	*home;
}	t_shell;

/* Signal */
void			sig_handling_set(int signals);
void			sighand(int sig);

/* ReadLine */
extern void		rl_replace_line(const char *text, int clear_undo);

/* Utils */
int				ft_strcmp(char *s1, char *s2);
int				ft_isbuiltin(char *cmd);
char			*ft_pathfinder(char *cmd, char **envp);
char			*ft_get_home(t_shell *shell);
int				ft_find_lenght(char **s);

/* Utils Token */
char 			*ft_strip(char **s);
int				ft_contained(char c, char const *set);
int 			findParenth(const char *s, int start);
char 			*getSub(const char *s, int start, int end);
int 			getCmd_aux(char *s, int *i);
int    			ft_pipe_check(char *cmd);
int    			ft_and_check(char *cmd);
int    			ft_quote_check(char *cmd);
char			*ft_arg_check(char *cmd, char **envp);
int				ft_bracket_aux(char *cmd);
int				ft_bracket_check(char *cmd);
int 			ft_check_operator(char *cmd);

/* Main */
int				main_loop(t_shell *s_shell);

/* Built in */
void			ft_pwd(void);
void			ft_cd(t_shell *shell);
void			ft_update_env(t_shell *shell, char *path);
void			ft_envhandle(char **envp, t_shell *shell);
void			ft_builtin(char *cmd, t_shell *shell);
void			ft_export(t_shell *shell);
void			ft_echo(t_shell *shell);
void			ft_unset(t_shell *shell);
void 			ft_exec_builtin(char *cmd, t_shell *shell);
void			ft_printenv(char **envp);

/* Parsing */
char			*getCmd(char *s, char **envp);
void			ft_start(t_shell *shell);

/* Pipe */


#endif