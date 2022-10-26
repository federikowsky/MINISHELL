/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-aless <md-aless@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:23 by agenoves          #+#    #+#             */
/*   Updated: 2022/10/26 12:43:54 by md-aless         ###   ########.fr       */
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
	char	**token;
	char	**token_temp;
	char	**operator;
	char	**operator_temp;
	char	*last_operator;
	int		exitstatus;
	int		prev_exitstatus;
	int		fd_in;
	int		fd_out;
	int		redirec;
	int		is_subshell;
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
int				ft_mat_lenght(char **s);
void			ft_print_mat(char **ss);
int				free_matrix(char **matrix);
char			**ft_mat_copy(char **mat);
void			ft_increase_shlvl(char ***mat);
char			*ft_get_pwd(t_shell *shell);

/* Utils Token */
char			*ft_strip(char **s);
int				ft_has(char c, char const *set);
int				findparenth(const char *s, int start, char *c);
char			*getsub(const char *s, int start, int end);
int				ft_get_cmd_aux(char *s, int *i);
int				ft_pipe_check(char *cmd);
int				ft_and_check(char *cmd);
int				ft_quote_check(char *cmd);
char			*ft_arg_check(char *cmd, char **envp, int redi);
int				ft_bracket_aux(char *cmd);
int				ft_bracket_check(char *cmd);
int				ft_check_operator(char *cmd);
int				ft_redir_check(char *cmd);
char			**ft_addelement(char **ss, char *cmd);
int				ft_check_builtin(char *input);
int				ft_findquote(char *s, int start);
char			*ft_check_quote(char **token);

/* Utils Redirection */
int				ft_find_redir(t_shell *shell);
void			ft_redirection(t_shell *shell);
void			ft_skip_redirection(t_shell *shell);

/* Main */
int				main_loop(t_shell *s_shell, char **envp);
void			ft_initializer(t_shell *shell);

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
char			*ft_get_cmd(char *s, char **envp);
int				ft_start(t_shell *shell);
void			ft_exec_cmd(t_shell *shell);
void			ft_exec_cmd_fork(t_shell *shell);
void			ft_switch_op(t_shell *shell);
void			ft_creatematrix(t_shell *shell);
void			ft_append_cmd(t_shell *shell);
char			*ft_get_op(t_shell *shell, int heredoc);
char			*ft_get_echo2(char *token);

/* Pipe */
void			ft_exec_pipe(t_shell *shell, int nb_pipe);
void			ft_pipe(t_shell *shell);
int				ft_count_pipe(t_shell *shell);

/* Bonus */
void			ft_or(t_shell *shell);
void			ft_and(t_shell *shell);

/* Subshell */
void			ft_run_new_shell(t_shell *shell);
int				ft_is_subshell(char *s);
void			ft_subshell(t_shell *shell, char *s);
void			ft_debug(t_shell *shell, int pipes[], int i);

/* Redirection*/
int				ft_right_redir(t_shell *shell);
void			ft_redir_exec(t_shell *shell);

void			ft_left_redir(t_shell *shell);

/* Heredoc*/
void			ft_heredoc(t_shell *shell);

/* Echo */
char			*ft_get_echo(char *s);
char			*ft_charjoin(char *s1, char s2);

#endif
