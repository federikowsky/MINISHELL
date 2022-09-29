/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:23 by agenoves          #+#    #+#             */
/*   Updated: 2022/09/29 16:36:37 by fefilipp         ###   ########.fr       */
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
	char	**cmds;
	char	**pipes;
	char	*path;
	char	*cmd;
	char	*home;
	int		cmd_count;
	int		is_pipe;
}	t_shell;

typedef struct s_tree
{
	char			*cmd;
	int				operator;
	int				subshell;
	struct s_tree	*sx;
	struct s_tree	*dx;
}	t_tree;

/* Signal */
void			sig_handling_set(int signals);
void			sighand(int sig);

/* ReadLine */
extern void		rl_replace_line(const char *text, int clear_undo);

/* Utils Token */
char 			*ft_strip(char **s);
int				ft_contained(char c, char const *set);
int 			findParenth(const char *s, int start);
char 			*getSub(const char *s, int start, int end);
int 			getCmd_aux(char *s, int *i);
int    			ft_pipe_check(char *cmd);
int    			ft_and_check(char *cmd);
int    			ft_quote_check(char *cmd);
int    			ft_bracket_check(char *cmd);
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

/* Parsing */
char			*getCmd(char *s);


/* Pipe */
void 			exec_pipe(t_shell *shell);
void 			run_cmd(t_shell *shell);

#endif