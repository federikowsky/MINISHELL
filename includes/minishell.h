/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fefilipp <fefilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:23 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/07 03:55:42 by fefilipp         ###   ########.fr       */
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
# define sstoken *(shell->token)
# define ssoperator *(shell->operator)
# define sslastop   (shell->last_operator)

typedef struct s_shell
{
	char	**env;
	char	*cmd;
	char	*home;
	char 	**token;
	char 	**token_temp;
	char	**operator;
	char	**operator_temp;
	char	*last_operator;
	int		exitstatus;
	int		prev_exitstatus;
	int		fd;
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
void			ft_print_mat(char **ss);
int				free_matrix(char **matrix);
char			**ft_mat_copy(char **mat);
void			ft_increase_shlvl(char ***mat);

/* Utils Token */
char			*ft_strip(char **s);
int				ft_has(char c, char const *set);
int				findparenth(const char *s, int start);
char			*getsub(const char *s, int start, int end);
int				getcmd_aux(char *s, int *i);
int				ft_pipe_check(char *cmd);
int				ft_and_check(char *cmd);
int				ft_quote_check(char *cmd);
char			*ft_arg_check(char *cmd, char **envp);
int				ft_bracket_aux(char *cmd);
int				ft_bracket_check(char *cmd);
int				ft_check_operator(char *cmd);
char 			**ft_addelement(char **ss, char *cmd);
int				ft_check_builtin(char *input);

/* Main */
int				main_loop(t_shell *s_shell, char **envp);

/* Built in */
int				ft_builtin(char *cmd, t_shell *shell);
int				ft_unset(t_shell *shell);
int				ft_export(char *s, t_shell *shell);
char			*ft_pwd(void);
void			ft_cd(t_shell *shell);
void			ft_update_env(t_shell *shell, char *path);
void			ft_envhandle(char **envp, t_shell *shell);
void			ft_echo(t_shell *shell);
void			ft_exit(t_shell *shell);
void			ft_exec_builtin(char *cmd, t_shell *shell);
void			ft_printenv(char **envp);

/* Parsing */
char			*getcmd(char *s, char **envp);
int				ft_start(t_shell *shell);
void 			ft_exec_cmd(t_shell *shell);
void			ft_switch_op(t_shell *shell);

/* Pipe */
void 			ft_exec_pipe(t_shell *shell, int nb_pipe);
void			ft_pipe(t_shell *shell);
int 			ft_count_pipe(t_shell * shell);

/* Bonus */
void			ft_or(t_shell *shell);
void			ft_and(t_shell *shell);

/* Subshell */
void			ft_run_new_shell(t_shell *shell);
int				ft_is_subshell(char *s);
void 			ft_subshell(t_shell *shell, char *s);

#endif
